int xor_sum(int x) {
	if (x < 0)
		return 0;
	int r = x % 4;
	switch (r) {
		case 0:
			return x;
		case 1:
			return 1;
		case 2:
			return x + 1;
		case 3:
			return 0;
	}
}