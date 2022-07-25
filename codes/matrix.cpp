namespace math {
	int mod = 0;
	
	template<int N, int M = N, typename T = int>
	class matrix {
		public:
			matrix() {
				memset(_m, 0, sizeof(_m));
			}
			matrix(const matrix& m) {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						this->_m[i][j] = m._m[i][j];
			}
			matrix(std::initializer_list<std::initializer_list<T>> l) {
				memset(_m, 0, sizeof(_m));
				int line = 0;
				for (auto&& i : l) {
					int colomn = 0;
					for (auto&& j : i) {
						this->_m[line][colomn] = mod ? j % mod : j;
						++colomn;
					}
					++line;
				}
			}

			matrix& operator = (const matrix& m) noexcept {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						this->_m[i][j] = m._m[i][j];
				return *this;
			}
			matrix& operator = (const T& a) noexcept {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						this->_m[i][j] = mod ? a % mod : a;
				return *this;
			}
			T* operator [] (const int& i) {
				if (i < 0 || i >= N)
					throw std::range_error("subscript invalid");
				return _m[i];
			}
			matrix operator + (const matrix& m) const {
				matrix temp(*this);
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j) {
						temp._m[i][j] += m._m[i][j];
						mod ? temp._m[i][j] %= mod : 0;
					}
				return temp;
			}
			matrix operator - (const matrix& m) const {
				matrix temp(*this);
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j) {
						temp._m[i][j] -= m._m[i][j];
						mod ? temp._m[i][j] %= mod : 0;
					}
				return temp;
			}
			matrix& operator += (const matrix& m) {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j) {
						this->_m[i][j] += m._m[i][j];
						mod ? this->_m[i][j] %= mod : 0;
					}
				return *this;
			}
			matrix& operator -= (const matrix& m) {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j) {
						this->_m[i][j] -= m._m[i][j];
						mod ? this->m[i][j] %= mod : 0;
					}
				return *this;
			}
			template<int i, int j, int k, typename T2>
			friend matrix<i, k, T2> operator * (const matrix<i, j, T2>& a, const matrix<j, k, T2>& b);
			template<int N2, typename T2>
			friend matrix<N2, N2, T2>& operator *= (matrix<N2, N2, T2>& a, const matrix<N2, N2, T2>& b);
			friend std::ostream& operator << (std::ostream& out, const matrix<N, M, T>& m) {
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < M; ++j)
						out << m._m[i][j] << ' ';
					if (i != N - 1)
						out << '\n';
				}
				return out;
			}
			friend std::istream& operator >> (std::istream& in, matrix<N, M, T>& m) {
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						in >> m._m[i][j];
				return in;
			}
			template <int U = N>
			typename std::enable_if<U == M, matrix<N, N, T>&>::type pow(long long k) {
				matrix base(*this);
				*this = matrix<N, N, T>::E();
				while (k) {
					if (k & 1)
						*this *= base;
					base *= base;
					k >>= 1;
				}
				return *this;
			}
			template <int U = N>
			static typename std::enable_if<U == M, matrix<N, N, T>>::type E() {
				static matrix<N, N, T> temp;
				if (temp._m[0][0] == 1)
					return temp;
				for (int i = 0; i < N; ++i)
						temp._m[i][i] = 1;
				return temp;
			}
		
		protected:
			T _m[N][M];
	};

	template<int i, int j, int k, typename T2>
	matrix<i, k, T2> operator * (const matrix<i, j, T2>& a, const matrix<j, k, T2>& b) {
		matrix<i, k, T2> temp;
		for (int _i = 0; _i < i; ++_i)
			for (int _k = 0; _k < k; ++_k)
				for (int _j = 0; _j < j; ++_j) {
					T2 t = a._m[_i][_j] * b._m[_j][_k];
					temp._m[_i][_k] += mod ? t % mod : t;
					mod ? temp._m[_i][_k] %= mod : 0;
				}
		return temp;
	}

	template<int N2, typename T2>
	matrix<N2, N2, T2>& operator *= (matrix<N2, N2, T2>& a, const matrix<N2, N2, T2>& b) {
		return a = a * b;
	}
}