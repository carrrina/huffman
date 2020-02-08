#include "huffman.h"

int treeNode_compare(const void* a_pointer, const void* b_pointer) {
	TreeNode a, b;
	a = *(TreeNode*) a_pointer;
	b = *(TreeNode*) b_pointer;
	if (a->frequency > b->frequency) {
		return -1;
	} else if (a->frequency < b->frequency) {
		return 1;
	} else {
		return 0;
	}
}

TreeNode initHuffman(double frequency,
					 unsigned char value,
					 TreeNode left,
					 TreeNode right) {
	//TODO 1
	TreeNode t = NULL;
	t = malloc(sizeof(struct treeNode));
	t->value = value;
	t->frequency = frequency;
	t->left = left;
	t->right = right;
	t->idx = -1;
	return t;
}

TreeNode createHuffmanTree(char *text) {
	//TODO 2
	int freq[127] = { 0 }, i, nr = 0;
	for (i = 0; i < strlen(text); i++)
		freq[(int)text[i]]++;
	for (i = 0; i < 127; i++)
		if (freq[i])
			nr++;
	TreeNode *nodes;
	nodes = malloc(nr * sizeof(struct treeNode));
	nr = 0;
	for (i = 0; i < 127; i++)
		if (freq[i]) {
			nodes[nr] = initHuffman(freq[i], i, NULL, NULL);
			nr++;
		}
	Heap h = initHeap(&treeNode_compare);
	for (i = 0; i < nr; i++) {
		h = insertHeap(h, nodes[i]);
	}
	TreeNode x, y, z;
	while (h->size > 1) {
		x = extractMax(h);
		y = extractMax(h);
		z = initHuffman(x->frequency + y->frequency, 0, x, y);
		h = insertHeap(h, z);
	}
	return extractMax(h);  
}

int found(TreeNode huffman, int caracter) {
	if (huffman->left == NULL && huffman->right == NULL) {
		if (huffman->value == caracter) 
			return 1;
		else
			return 0;
	}
	if (found(huffman->left, caracter))
		return 1;
	if (found(huffman->right, caracter))
		return 1;
	return 0;
}

void traverse(TreeNode huffman, char *s, int caracter) {
	if (huffman->left == NULL && huffman->right == NULL) {
		return;
	}
	TreeNode aux = huffman->left;
	if (found(aux, caracter)) {
		strcat(s, "0");
		traverse(huffman->left, s, caracter);
	}
	else {
		strcat(s, "1");
		traverse(huffman->right, s, caracter);
	}
}

char coded[200];

char *compress(TreeNode huffman, char *text) {
	//TODO 3
	int i;
	char s[200];
	s[0] = '\0';
	traverse(huffman, s, text[0]);
	strcpy(coded, s);
	for (i = 1; i < strlen(text); i++) {
		strcat(coded, " ");
		strcpy(s, "\0");
		traverse(huffman, s, text[i]);
		strcat(coded, s);
	}
	return coded;
}

char decoded[200];

char *decompress(TreeNode huffman, char *text) {
	//TODO 4
	decoded[0] = '\0';
	char c[200], aux[2];
	int i, j;
	TreeNode t = huffman;
	c[0] = '\0';
	aux[0] = '\0';
	aux[1] = '\0';
	for (i = 0; i <= strlen(text); i++) {
		if (text[i] == ' ') {
			for (j = 0; j < strlen(c); j++)
				if (c[j] == '1')
					t = t->right;
				else if (c[j] == '0')
					t = t->left;
			aux[0] = t->value;
			strcat(decoded, aux);
			strcpy(c, "\0");
			t = huffman;
			continue;
		}
		aux[0] = text[i];
		strcat(c, aux);
	}
	//pt ultimul caracter
	for (j = 0; j < strlen(c); j++)
		if (c[j] == '1')
			t = t->right;
		else if (c[j] == '0')
			t = t->left;
		aux[0] = t->value;
		strcat(decoded, aux);
	return decoded;
}

TreeNode freeTree(TreeNode root) {
	//TODO 5
	if (root == NULL)
		return NULL;
	if (root->left != NULL)
		freeTree(root->left);
	if (root->right != NULL)
		freeTree(root->right);
	free(root);
	return NULL;
}
