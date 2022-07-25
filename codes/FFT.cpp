class Complex {
	public:
		double r, i;
		Complex(const double& a = 0, const double& b = 0) : r(a), i(b) {}
		Complex(const Complex& a) : r(a.r), i(a.i) {}

		Complex operator + (const Complex& a) {
			return Complex(this->r + a.r, this->i + a.i);
		}

		Complex operator - (const Complex& a) {
			return Complex(this->r - a.r, this->i - a.i);
		}

		Complex operator * (const Complex& a) {
			return Complex(this->r * a.r - this->i * a.i, this->r * a.i + this->i * a.r);
		}
};
void FFT(Complex *a, const int& opt);

const int N = 6e6+5;
const double PI = acos(-1);

int n, m, lim, len;
int rev[N];
Complex F[N], G[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i)
		scanf("%lf", &F[i].r);
	for (int i = 0; i <= m; ++i)
		scanf("%lf", &G[i].r);

	lim = 1, len = 0;
	while (lim <= n + m)
		lim <<= 1, len++;
	
	for (int i = 0; i < lim; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
		
	// 正变换
	FFT(F, 1);
	FFT(G, 1);
	
	for (int i = 0; i < lim; i++)
		F[i] = F[i] * G[i];
	// 逆变换
	FFT(F, -1);

	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(F[i].r + 0.5));
	return 0;
}

void FFT(Complex *a, const int& opt) {
	for (int i = 0; i < lim; ++i)
		if (i < rev[i])
			std::swap(a[i], a[rev[i]]);
	for (int dep = 1; dep <= log2(lim); ++dep) {
		int m = 1 << dep;
		Complex wn(cos(2.0 * PI / m), opt * sin(2.0 * PI / m));
		for (int k = 0; k < lim; k += m) {
			Complex w(1);
			for (int j = 0; j < m / 2; ++j) {
				Complex t = w * a[k + j + m / 2], u = a[k + j];
				a[k + j] = u + t;
				a[k + j + m / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (opt == -1)
		for (int i = 0; i < lim; ++i)
			a[i].r /= lim;
}