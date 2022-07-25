#define _getch() ((p >= SIZE ? std::fread(buf, sizeof(char), SIZE, stdin), p = 1, buf[0] : buf[p++]))
#define _isdigit(a) ((a) >= '0' && (a) <= '9')
#define _isalpha(a) (((a) >= 'a' && (a) <= 'z') || ((a) >= 'A' && (a) <= 'Z'))
#define _showable(a) ((a) > 32 && (a) <= 126)

class IO final{
	private:
		IO() = delete;
		const static int SIZE = 1 << 20;
		static char buf[SIZE];
		static int p;

	public:
		static char getchar() {
			char c;
			for (c = _getch(); !_showable(c); c = _getch());
			return c;
		}
		template <typename ...Args>
		static void read(Args&&... args) {
			auto readint = [](auto&& x)->void {
				x = 0;
				char c;
				for (c = _getch(); (!_isdigit(c)) && c != '-'; c = _getch());
				int sign = c == '-' ? c = _getch(), -1 : 1;
				for (; _isdigit(c); c = _getch())
					x = (x << 3) + (x << 1) + c - '0';
				x *= sign;
			};
			std::initializer_list<bool>{(readint(std::forward<Args>(args)), false)...};
		}

		template <typename ...Args>
		static void print(const int& x, Args... args) {
			printf("%d", x);
			std::initializer_list<bool>{(printf(" %d", std::forward<Args>(args)), false)...};
			printf("\n");
		}

		template <typename ...Args>
		static void print(const long long& x, Args... args) {
			printf("%lld", x);
			std::initializer_list<bool>{(printf(" %lld", std::forward<Args>(args)), false)...};
			printf("\n");
		}
};

int IO::p = IO::SIZE;
char IO::buf[IO::SIZE];