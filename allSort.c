#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10000000

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
//selection sort
void selectionSort(int *array, int size) {
	for (int i = 0; i < size; i++) {
		int k = i;
		for (int j=i+1; j < size; j++) {
			if (array[j] < array[k]) {
				k = j;
			}
		}
		if (k != i) {
			swap(array[i], array[k]);
		}
	}
}
//insert sort
void insertSort(int *array, int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j > 0 && array[j] < array[j-1]) {
			swap(array[j], array[j-1]);
			j = j-1;
		}
	}
}
//heap sort
typedef struct Heap {
	int elements[SIZE];
	int capacity;
	int currentSize;
} heap;
int getParentIndex(int child) {
	if ((int)child/2 == 0) {
		return -1;
	}
	return (int)child/2;
}
int getLeftchildIndex(int parent) {
	return 2*parent;
}
void bubble_up(heap* p, int currentSize) {
	if (getParentIndex(currentSize) == -1) {
		return;
	}
	if (p->elements[getParentIndex(currentSize)] > p->elements[currentSize]) {
		swap(p->elements[getParentIndex(currentSize)], p->elements[currentSize]);
		bubble_up(p, getParentIndex(currentSize));
	}
}
void bubble_down(heap* p, int minIndex) {
	int minindex = minIndex;
	int lc = getLeftchildIndex(minIndex);
	for (int i = 0; i <= 1; i++) {
		if (lc+i <= p->currentSize) {
			if (p->elements[lc+i] < p->elements[minindex]) {
				minindex = lc+i;
			}
		}
	}
	if (minindex != minIndex) {
		swap(p->elements[minIndex], p->elements[minindex]);
		bubble_down(p, minindex);
	}
}
void insertHeap(heap* p, int element) {
	//the index is 1,2,3,.....,capacity-1
	if (p->currentSize+1 >= p->capacity) {
		printf("The heap is full!\n");
		return;
	} else {
		p->currentSize = p->currentSize+1;
		p->elements[p->currentSize] = element;
		bubble_up(p, p->currentSize);
	}
}
void deleteMin(heap* p, int& minValue) {
	if (p->currentSize == 0) {
		printf("The heap is empty!\n");
		return;
	} else {
		minValue = p->elements[1];
		p->elements[1] = p->elements[p->currentSize];
		p->currentSize = p->currentSize-1;
		bubble_down(p, 1);
	}
}
void heapSort(int *elements, int size) {
	heap* p = (heap*)malloc(sizeof(heap));
	p->capacity = SIZE;
	p->currentSize = 0;
	/*
	for (int i=0; i<size; i++) {
		insertHeap(p, elements[i]);
	}*/	
	for (int i = 0; i < size; i++) {
		p->elements[++p->currentSize]=elements[i];
	}
	for (int i = p->currentSize; i >= 1; i--) {
		bubble_down(p, i);
	}

	int minValue=0;
	for (int i = 0; i < size; i++) {
		deleteMin(p, minValue);
		elements[i] = minValue;
	}

}
//merge sort
void merge(int* array, int low, int middle, int high) {
	//temp is temporarily holding the sorted array, array is sorted in the two half seperately
	int* temp = (int*)malloc(sizeof(int)*(high-low+1));
	int i = low;
	int j = middle+1;
	int k = 0;
	while (i <= middle && j <= high) {
		if (array[i] < array[j]) {
			temp[k++] = array[i++];
		} else {
			temp[k++] = array[j++];
		}
	}
	while (i <= middle) {
		temp[k++] = array[i++];
	}
	while (j <= high) {
		temp[k++] = array[j++];
	}
	//please pay attention to here low+i
	for (i = 0; i < k; i++) {
		array[low+i] = temp[i];
	}
	free(temp);
}
void mergeSort(int* array, int low, int high) {
	int middle;
	if (low < high) {
		middle = (low+high)/2;
		mergeSort(array, low, middle);
		mergeSort(array, middle+1, high);
		merge(array, low, middle, high);
	}
}
//quick sort
int partition(int* array, int low ,int high) {
	int middle = (low+high)/2;
	swap(array[middle], array[high]);
	int pivot = array[high];
	//pivotLoc = low not 0
	int pivotLoc = low;
	for (int i = low; i < high; i++) {
		if (array[i] < pivot) {
			swap(array[pivotLoc], array[i]);
			pivotLoc++;
		}
	}
	swap(array[high], array[pivotLoc]);
	return pivotLoc;
}
void quickSort(int* array, int low, int high) {
	int pivotLoc;
	//if ((high-1)>0) this is wrong, otherwise there is segment error
	if (low < high) {
		pivotLoc = partition(array, low, high);
		quickSort(array, low, pivotLoc-1);
		quickSort(array, pivotLoc+1, high);
	}
}
int main() {
	int size;
	int *array;
	int number;
	int selection;
    while(true) {
		printf("please enter the size of the arrray:\n");
		scanf("%d", &size);
		array = (int*)malloc(size*sizeof(int));
		for (int i = 0; i < size; i++) {
			array[i] = rand()%size;
		}
	
		printf("please select the sort algorithm: \n1. selectionSort   2. insertSort   3. heapSort   4. mergeSort   5. quickSort\n");
		scanf("%d", &selection);

		clock_t start = clock();
		switch(selection) {
			case 1:
				selectionSort(array, size);
				break;
			case 2:
				insertSort(array, size);
				break;
			case 3:
				heapSort(array, size);
				break;
			case 4:
				mergeSort(array, 0, size-1);
				break;
			case 5:
				quickSort(array, 0, size-1);
				break;
		}	
		clock_t end = clock();
		printf("The running time is %lf ms and %lf s\n", (double)end-start, (double)(end-start)/1000);
	}
	return 0;
}

