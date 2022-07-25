namespace c_geo {
	template <typename T = double>
	class vector2D final{
		public:
			vector2D() {
				this->x = 0;
				this->y = 0;
			}
			vector2D(T x, T y) {
				this->x = x;
				this->y = y;
			}
			vector2D(const vector2D<T>& a) {
				this->x = a.x;
				this->y = a.y;
			}

			double modulus() const {
				return std::sqrt(this->x * this->x + this->y * this->y);
			}
			T modulusNoSqrt() const {
				return this->x * this->x + this->y * this->y;
			}
			bool parallel (const vector2D<T>& a) const {
				return this->cross(a) == 0;
			}
			vector2D rotate(const double alpha) const {
				double _cos = cos(alpha), _sin = sin(alpha);
				return vector2D(x * _cos - y * _sin, y * _cos + x * _sin);
			}
			double k() const {
				return (double)y / x;
			}
			double alpha() const {
        return acos(this->cross(vector2D<double>(1, 0)) / this->modulus());
			}
			vector2D operator - (const vector2D<T>& a) const {
				return vector2D(this->x - a.x, this->y - a.y);
			}
			vector2D operator + (const vector2D<T>& a) const {
				return vector2D(this->x + a.x, this->y + a.y);
			}

			bool operator == (const vector2D<T>& a) const {
				return this->x == a.x && this->y == a.y;
			}

			// dot product
			T operator * (const vector2D<T>& a) const {
				return this->x * a.x + this->y * a.y;
			}
			vector2D operator * (const T& a) const {
				return vector2D(this->x * a, this->y * a);
			}
			T cross(const vector2D<T>& a) const {
				return this->x * a.y - this->y * a.x;
			}
			friend vector2D operator * (const T& a, const vector2D<T>& b) {
				return vector2D(b.x * a, b.y * a);
			}
			friend std::istream& operator >> (std::istream& in, vector2D<T>& a) {
				return in >> a.x >> a.y;
			}
			friend std::ostream& operator << (std::ostream& out, const vector2D<T>& a) {
				return out << a.x << ' ' << a.y;
			}

			T x, y;
	};
}