#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test, score) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
		else \
			total_score += score; \
	} while (0)

int tests_run = 0;
float total_score = 0;

int test1[] = {10, 9, 7, 5, 12, 4, 20, 6, 8, -8, 15};
int test2[] = {20, 10, 26, 94, 7, 66, 64, 37, 62, 92, 31, 91, 68, 19, 12, 55, 38, 32, 2, 18, 72, 92};

int int_compare(const void* a_pointer, const void* b_pointer) {
    return *(int*)a_pointer - *(int*) b_pointer;
}

void drawHeapAux(Heap h, int index, FILE* stream) {
    static int nullcount = 0;

    if (2 * index + 1 < h->size) {
    	int left = 2 * index + 1;
        fprintf(stream, "    %d -> %d;\n", h->vector[index], h->vector[left]);
        drawHeapAux(h, left, stream);
    }
    if (2 * index + 2 < h->size) {
    	int right = 2 * index + 2;
        fprintf(stream, "    %d -> %d;\n", h->vector[index], h->vector[right]);
        drawHeapAux(h, right, stream);
    }
}

void drawHeap(Heap h, int index, char *fileName) {
	FILE* stream = fopen("test.dot", "w");
	char buffer[SIZE];
    fprintf(stream, "digraph HEAP {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
    if (!h)
        fprintf(stream, "\n");
    else if (2 * index + 1 > h->size)
        fprintf(stream, "    %d;\n", h->vector[index]);
    else
        drawHeapAux(h, index, stream);
    fprintf(stream, "}\n");
    fclose(stream);
    sprintf(buffer, "dot test.dot | neato -n -Tpng -o %s", fileName);
	system(buffer);
}

int checkHeap(Heap h, int index) {
	if (h->size == 0) {
		return 0;
	}
	int leftChildIndex, rightChildIndex;
	leftChildIndex = 2 * index + 1;
	rightChildIndex = leftChildIndex + 1;
	int result = 1;
	if (leftChildIndex < h->size) {
		if (h->compare_func(&h->vector[index], &h->vector[leftChildIndex]) < 0) {
			return 0;
		} else {
			result = result && checkHeap(h, leftChildIndex);
		}
	}
	if (rightChildIndex < h->size) {
		if (h->compare_func(&h->vector[index], &h->vector[rightChildIndex]) < 0) {
			return 0;
		} else {
			result = result && checkHeap(h, rightChildIndex);
		}
	}
	return result;
}

static char *test_insert() {
	int i;
	Heap h = initHeap(&int_compare);
	for (i = 1; i <= test1[0]; i++) {
		h = insertHeap(h, test1[i]);
	}
	drawHeap(h, 0, "prob1_test1.png");
	sd_assert("Problema1 - Test1 picat", checkHeap(h, 0));
	h = freeHeap(h);
	h = initHeap(&int_compare);
	for (i = 1; i <= test2[0]; i++) {
		h = insertHeap(h, test2[i]);
	}
	drawHeap(h, 0, "prob1_test2.png");
	sd_assert("Problema1 - Test2 picat", checkHeap(h, 0));
	h = freeHeap(h);
	return 0;
}

static char *test_extract_max() {
	int i;
	Heap h = initHeap(&int_compare);
	for (i = 1; i <= test1[0]; i++) {
		h = insertHeap(h, test1[i]);
	}
	drawHeap(h, 0, "prob2_test1.png");
	sd_assert("Problema2 - Test1 picat", extractMax(h) == 20 && checkHeap(h, 0));
	drawHeap(h, 0, "prob2_test1_1.png");
	h = freeHeap(h);
	h = initHeap(&int_compare);
	for (i = 1; i <= test2[0]; i++) {
		h = insertHeap(h, test2[i]);
	}
	drawHeap(h, 0, "prob2_test2.png");
	sd_assert("Problema2 - Test2 picat", extractMax(h) == 94 && checkHeap(h, 0));
	drawHeap(h, 0, "prob2_test2_1.png");
	h = freeHeap(h);
	return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 2);
	sd_run_test(test_extract_max, 2);
	return 0;
}

int main() {
	srand(time(NULL));
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("Toate testele au trecut! Felicitari!\n");
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}