template <typename toSS>
class SearchSort {
private:
	
public:
	// searching
	int binarySearch(int length, toSS toFind,toSS toSearch[]);
	int sequentialSearch(int length, toSS toFind, toSS toSearch[]);
	
	//sorting
	void insertionSort(int length, toSS[]);
	void selectionSort(int length, toSS[]);
};