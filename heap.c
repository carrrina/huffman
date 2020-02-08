#include "heap.h"

Heap initHeap(int (*compare_func) (const void*, const void*)) {
	//TODO 1
	Heap h = malloc(sizeof(struct heap));
	h->size = 0;
	h->capacity = 100;
	h->compare_func = compare_func;
	return h;
}

Heap siftDown(Heap h, int index) {
	//TODO 2
	//HINT: Se va folosi funcția swapAndSiftDown
	int l = 2 * index + 1, r = 2 * index + 2, maxi = index;
	if (l < h->size && h->compare_func(&h->vector[l], &h->vector[maxi]) > 0)
		maxi = l;
	if (r < h->size && h->compare_func(&h->vector[r], &h->vector[maxi]) > 0)
		maxi = r;
	if (index != maxi) 
		h = swapAndSiftDown(h, index, maxi);
	return h;
}

Heap siftUp(Heap h, int index) {
	//TODO 3
	Type aux;
	while (index > 0 && h->compare_func(&h->vector[(index - 1) / 2], &h->vector[index]) < 0) {
		aux = h->vector[index];
		h->vector[index] = h->vector[(index - 1) / 2];
		h->vector[(index - 1) / 2] = aux;
		index = (index - 1) / 2;
	}
	return h;
}

Heap swapAndSiftDown(Heap h, int parent, int child) {
	//TODO 4
	Type aux = h->vector[parent];
	h->vector[parent] = h->vector[child];
	h->vector[child] = aux;
	h = siftDown(h, child); 
	return h;
}

Heap insertHeap(Heap h, Type element) {
	//TODO 5
	//HINT: Se va folosi funcția siftUp.
	if (h->size == h->capacity)
		return h;
	h->size++;
	h->vector[h->size - 1] = element;
	h = siftUp(h, h->size - 1);
	return h;
}

Type extractMax(Heap h) {
	//TODO 6
	//HINT: Se va folosi funcția siftDown
	Type max = h->vector[0];
	h->vector[0] = h->vector[h->size - 1];
	h->size--;
	h = siftDown(h, 0);
	return max;
}

Heap freeHeap(Heap h) {
	//TODO 7
	if (h != NULL) 	
		return h;
	Type aux;
	while (h->size > 0)
		aux = extractMax(h);
	free(h);
	return NULL;
}

