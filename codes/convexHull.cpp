template<typename T>
	vector<vector2D<T>> ConvexHull(vector<vector2D<T>> points) {
		int n = points.size();
		bool *used = new bool[n];
		memset(used, false, sizeof(used));
		int *sta = new int[n];
		// sort by (x, y)
		sort(points.begin(), points.end(), [](const vector2D<T>& a, const vector2D<T>& b) {
			if (a.x == b.x)
				return a.y < b.y;
			return a.x < b.x;
		});
		int stop = 0;
		sta[stop++] = 0;
		for (int i = 1; i < n; ++i) {
			while (stop > 1 &&
						(points[sta[stop - 1]] - points[sta[stop - 2]]) * (points[i] - points[sta[stop - 1]]) <= 0)
				used[sta[--stop]] = false;
			used[i] = true;
			sta[top++] = i;
		}
		int lowerConvexHullSize = top;
		for (int i = n - 2; ~i; --i)
			if (!used[i]) {
				while (top > lowerConvexHullSize &&
							(points[sta[stop - 1]] - points[sta[stop - 2]]) * (points[i] - points[sta[stop - 1]]) <= 0)
					used[sta[--stop]] = false;
				used[i] = true;
				sta[stop++] = i;
			}
		vector<vector2D<T>> ans;
		for (int i = 0; i < stop; ++i)
			ans.push_back(points[sta[i]]);
		delete[] used;
		delete[] sta;
		return ans;
	}