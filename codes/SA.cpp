namespace Random {
	template<typename T>
	class SA {
		protected:
			virtual double J(const T& state) const = 0;
			virtual T getNewState(const T& curState, const double& temperature) const = 0;
			virtual bool checkState(const T& state) const {
				return true;
			}

			// 起始温度
			double temperatureStart;
			// 最小温度
			double temperatureMin;
			double curJ;
			// 降温效率(0, 1)
			double coolingCoefficient;
			T result;
			// 随机种子
			unsigned int randSeed;

			enum Type{
				max = -1, min = 1
			};
			
			// 求值类别
			Type type;

			void once() {
				double temperature = temperatureStart;
				T temp = result;
				while (temperature > temperatureMin) {
					T now = getNewState(temp, temperature);
					if (!checkState(now)) {
						temperature *= coolingCoefficient;
						continue;
					}
					double nowJ = J(now);
					double deltJ = (nowJ - curJ) * type;
					if (deltJ < 0) {
						curJ = nowJ;
						result = temp = now;
					} else if (std::exp(-deltJ / temperature) * RAND_MAX > rand())
						temp = now;
					temperature *= coolingCoefficient;
				}
			}
		public:

			SA() {
				type = min;
				temperatureStart = 3000;
				temperatureMin = 1e-15;
				coolingCoefficient = 0.996;
				randSeed = 1e9 + 7;
			}
		
			T exec(const T& beginState, int times) {
				srand(randSeed);
				result = beginState;
				// curJ = 1e8;
				curJ = J(beginState);
				while (times--)
					this->once();
				return result;
			}

			double energy() const {
				return curJ;
			}
	};
}