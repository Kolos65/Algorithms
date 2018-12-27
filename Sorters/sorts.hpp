#ifndef SORTS_HPP
#define SORTS_HPP

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

/// ========== BUBURÉKRENDEZÉS ==========
void bubbleSort(int* A, int n) {

	for (int j = n - 1; j >= 1; --j) {
		for (int i = 0; i <= j - 1; ++i) {
			if (A[i] <= A[i + 1]) {
				//skip
			} else {
				swap(A[i], A[i + 1]);
			}
		}
	}

}

/// ========== MAXIMUM KIVÁLASZTÁSOS RENDEZÉS ==========
int MaxSel(const int* A, int j) {

	int ind = 0;
	for (int i = 0; i < j; ++i) {
		if (A[i + 1] > A[ind]) {
			ind = i + 1;
		}
	}
	return ind;

}

void maxSort(int* A, int n) {

	for (int j = n - 1; j >= 1; --j) {

		int ind = MaxSel(A, j);
		swap(A[ind], A[j]);
	}

}

/// ========== BESZÚRÓ RENDEZÉS ==========
void insertionSort(int* A, int n) {

	for (int j = 0; j <= n - 2; ++j) {
		int w = A[j + 1];
		int i = j;
		while (i >= 0 && A[i] > w)
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = w;
	}

}

#endif
