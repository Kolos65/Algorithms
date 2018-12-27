#include <iostream>
#include <cstdlib>
#include <ctime>                 //Időméréshez kell
#include <string.h>              //Tömb másoláshoz kell

#include "sorts.hpp"
#include "quicksort.hpp"

using namespace std;

/**    ----- Constansok -----   **/
const int n = 15;                		//A rendezéseket tesztelő tömb mérete
const int max_gen_value = 100; 			//A tömböt feltöltő egészek lehetséges maximális értéke
const size_t n2 = 50000;         		//A teljesítmény teszthez használt tömb mérete
const bool performance_test = false;    //Futassunk-e teljesítmény tesztet

/**    ----- Segéd függvény -----    **/
template<class T>
void printArray(T* A, int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

/**    ----- Main függvény -----    **/
int main() {
	srand(time(NULL));

	// Teszttömb generálása
	int testArray[n];
	for( int i = 0; i < n; ++i ) {
		testArray[i] = rand() % (max_gen_value + 1);  //tömb feltöltése random
		//testArray[i] = 2*n-i; 					  	//tömb feltöltése csökkenő elemekkel
	}
	cout << "Az eredeti tomb: "; printArray(testArray, n); cout << endl;

	int sortArray[n];		//Az aktuális rendezés mindig a "sortArray" segédtömbön történik
	size_t copysize = n*sizeof(int);
	cout << "Buborek: "; memcpy(sortArray, testArray, copysize); bubbleSort(sortArray, n); 			printArray(sortArray, n);
	cout << "Maximum: "; memcpy(sortArray, testArray, copysize); maxSort(sortArray, n); 			printArray(sortArray, n);
	cout << "Beszuro: "; memcpy(sortArray, testArray, copysize); insertionSort(sortArray, n); 		printArray(sortArray, n);
	cout << "Gyorsr.: "; memcpy(sortArray, testArray, copysize); Quicksort(sortArray, 0, n - 1); 	printArray(sortArray, n);


	/**    Teljesítményteszt    **/
	// A paramétert manuálisan tudjuk állítani a konstansok között
	if (performance_test) {
		cout << "\nTeljesitmenyteszt " << n2 << " elemu tombre nezve: \n";

		int testArray2[n2];     //A rendezendő tömb
		for (unsigned int i = 0; i < n2; i++)
			testArray2[i] = rand() % (max_gen_value + 1);  //tömb feltöltése

		int sortArray[n2];		//Az aktuális rendezés mindig a "sortArray" segédtömbön történik
		size_t copysize = n2*sizeof(int);
		clock_t start;
		cout << "Buborek: "; memcpy(sortArray, testArray2, copysize); start = clock(); bubbleSort(sortArray, n2); 		cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << " s" << endl;
		cout << "Maximum: "; memcpy(sortArray, testArray2, copysize); start = clock(); maxSort(sortArray, n2); 			cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << " s" << endl;
		cout << "Beszuro: "; memcpy(sortArray, testArray, copysize);  start = clock(); insertionSort(sortArray, n2); 	cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << " s" << endl;
		cout << "Gyorsr.: "; memcpy(sortArray, testArray2, copysize); start = clock(); Quicksort(sortArray, 0, n2 - 1); cout << ((double) (clock() - start) / CLOCKS_PER_SEC) << " s" << endl;
	}

	return 0;
}
