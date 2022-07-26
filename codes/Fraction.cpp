template <typename T>
class Fraction {
	private:
		// \frac{a}{b}
		T a, b;
	public:
		Fraction() : a(0), b(1) {}
		Fraction(T a, T b = 1) {
			assert(b != 0);
			if (b > 0)
				this->a = a, this->b = b;
			else
				this->a = -a, this->b = -b;
		}
		Fraction(const Fraction& f) : a(f.a), b(f.b) {}

		Fraction& simplify() {
			T g = __gcd(a, b);
			a = a / g;
			b = b / g;
			return *this;
		}
		
		Fraction operator + (const Fraction& f) const {
			Fraction res;
			res.b = b * f.b;
			res.a = a * f.b + b * f.a;
			return res.simplify();
		}

		Fraction operator - () const {
			return Fraction(-this->a, this->b);
		}

		Fraction operator - (const Fraction& f) const {
			return *this + (-f);
		}

		Fraction operator * (const Fraction& f) const {
			return Fraction(a * f.a, b * f.b).simplify();
		}

		Fraction operator / (const Fraction& f) const {
			assert(f.a != 0);
			return Fraction(a * f.b, b * f.a).simplify();
		}

		bool operator < (const Fraction& f) const {
			return a * f.b < b * f.a; 
		}

		bool operator == (const Fraction& f) const {
			return a * f.b == b * f.a;
		}

		double value() const {
			return (double)a / b;
		}

		friend ostream& operator << (ostream& out, const Fraction& f) {
			return out << f.a << '/' << f.b;
		}
};