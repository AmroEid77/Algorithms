#include "iostream"
#include "fstream"
#include "vector"


using namespace std;

template<typename T>
class Heap {// by default Max heap
private:
	vector<T> heap;
	int n;//currnet size
	int capacity;
	// I can add type for heap (Max or Min) but I was have something very urgent

	int parent(int i) { return (i - 1) / 2; }

	int leftChild(int i) { return 2 * i + 1; }

	int rightChild(int i) { return 2 * i + 2; }


public:

	Heap(int size=5);

	void insert(T value);

	int size()const;

	bool isEmpty()const;

	bool removeMaxElement();

	void heapify(int index);// hepaify for max

	void heapifyToMin(int index);

	void convertMaxHeapToMinHeap();

	void printHeap();



	
};

template<typename T>

Heap<T>::Heap(int size) {
	this->capacity = size;
	n = 0;
	heap.resize(capacity);
	
}

template<typename T>
void Heap<T>::insert(T value) {
	if (size() >= capacity) {
		heap.resize(capacity * 2);
	}
	int i = n;
	heap[n++] = value;

	//to make sure the heap still in maxHeap shape
	while (i != 0 && heap[parent(i)] < heap[i]) {
		T temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;

		i = parent(i);

	}

	/* //another solution from slides and same I need to change v to heap but the first index strat at 1 not 0
	n = n + 1; // preserve a space
    int i = n;

    // i is the child and i/2 is the parent
    // if i > 1, it is not the root, so it has a parent
    while (i > 1 && val > v[i / 2]) {
        v[i] = v[i / 2];
        i = i / 2;
    }

    v[i] = val;
	*/

}
template<typename T>
int Heap<T>::size()const {
	return n;
}
template<typename T>
bool Heap<T>::isEmpty()const {
	return n <= 0;
}

template<typename T>
bool Heap<T>::removeMaxElement() {
	if (isEmpty()) {//empty
		return false;
	}
	else if (size() == 1) {//if have only one element
		n--;
		return true;
	}
	else {
		T root = heap[0];
		heap[0] = heap[size() - 1];
		n--;
		heapify(0);
		return true;
	}
}

template<typename T>
void Heap<T>::heapify(int index) {

	int leftC = leftChild(index);
	int rightC = rightChild(index);
	int largest = index;
	
	if (leftC < size() && heap[leftC] > heap[largest])
		largest = leftC;

	if (rightC < size() && heap[rightC] > heap[largest])
		largest = rightC;
	if (largest != index) {
		// swap the values
		T temp = heap[index];
		heap[index] = heap[largest];
		heap[largest] = temp;

		heapify(largest);
	}
	/* //another solution but from slides and I need to change v to heap 
	int temp = v[i];
    int flag = 0;

    while (2 * i <= n && !flag) {
        int child = 2 * i;

        if (child + 1 < n && v[child] < v[child + 1]) {
            child = child + 1;
        }

        if (v[child] > temp) {
            v[i] = v[child];
            i = child;
        } else {
            flag = 1;
        }
    }

    v[i] = temp;
	*/
}

template<typename T>
void Heap<T>::heapifyToMin(int index) {

	int leftC = leftChild(index);
	int rightC = rightChild(index);
	int largest = index;

	if (leftC < size() && heap[leftC] < heap[largest])
		largest = leftC;

	if (rightC < size() && heap[rightC] < heap[largest])
		largest = rightC;

	if (largest != index) {
		// swap the values
		T temp = heap[index];
		heap[index] = heap[largest];
		heap[largest] = temp;

		heapifyToMin(largest);
	}
}
template<typename T>
void Heap<T>::convertMaxHeapToMinHeap() {
	for (int i = (size() / 2) - 1; i >= 0; --i) {
		heapifyToMin(i);
	}
}
template<typename T>
void Heap<T>::printHeap() {
	if (isEmpty()) {
		cout << "Heap is empty." << endl;
		return;
	}

	for (int i = 0; i < size(); i++) {
		cout << heap[i] << " ";
	}
}




int main() {
	Heap<int> heap;
	int x;
	ifstream file;	
	file.open("C:\\unversite files\\Secoend Year\\Data Structure\\HeapHomeWork\\readFile.txt");
	if (!file)
	{
		cout << "Cannot open file" << endl;
	}
	while (file >> x) {
		heap.insert(x);
	}
	file.close();
	/*heap.insert(5);
	heap.insert(4);
	heap.insert(3);
	heap.insert(10);
	heap.insert(11);
	heap.insert(90);
			Max heap
	           44
			  /  \
             42   35
			/  \    \ 
		  33    31  19  27
		10  26    14
	
	after HeapifyToMin (convert)
	           10
			  / \
             14   19
			/ \    \
		   26  31   90
	*/

	cout << "Print the Max heap \n";
	heap.printHeap();
	heap.convertMaxHeapToMinHeap();
	cout << "\nPirnt after convert to MinHeap\n";
	heap.printHeap();
	
	return 0;
}