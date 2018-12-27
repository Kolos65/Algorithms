#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP


void swapint(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

int Divide(int* A, int down, int up) {

	int pivot = A[down];
	int left = down;
	int right = up;

	while (left < right) {
		while (A[left] <= pivot && left < up) {
			left = left + 1;
		}
		while (A[right] >= pivot && right > down) {
            right = right - 1;
		}
		if (left < right) {
			swapint(A[left], A[right]);
		}
	}
	A[down] = A[right];
	A[right] = pivot;
	return right;

}

void Quicksort(int* A, int down, int up) {

	if (down < up) {
		int q = Divide(A, down, up);
		Quicksort(A, down, q - 1);
		Quicksort(A, q + 1, up);
	}

}

#endif
