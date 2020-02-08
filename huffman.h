#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#include<string.h>

typedef struct pair {
	unsigned char value;
	unsigned int appearances;
} Pair;

/**
*	Variabilă globală folosită pentru setarea id-ului unui nod, în funcția
* initHuffman.
**/
int idx;

/**
*	Inițializează un nod al arborelui de compresie Huffman, alocându-i și
* memorie.
**/
TreeNode initHuffman(double frequency,
					 unsigned char value,
					 TreeNode left,
					 TreeNode right);

/**
*	Funcție generică de comparare, folosită pentru heap.
**/
int treeNode_compare(const void* a_pointer, const void* b_pointer);

/**
*	Funcție care primește textul ce urmează a fi codificat și realizeaza
* arborele de compresie Huffman, pe baza acestuia.
**/
TreeNode createHuffmanTree(char *text);

/**
*	Funcție care va returna codificarea textului primit ca argument, determinată
* pe baza arborelui de compresie Huffman.
**/
char *compress(TreeNode huffman, char *text);

/**
*	Funcție care va returna decodificarea codului primit ca argument. Reprezintă
* inversa funcției compress.
**/
char *decompress(TreeNode huffman, char *text);

/**
*	Funcție care dealocă memoria alocată pentru un arbore de compresie.
**/
TreeNode freeTree(TreeNode root);
