#include "huffman.h"

void drawHuffmanAux(TreeNode huffman, FILE* stream) {
    static int nullcount = 0;

    if (huffman->left) {
    	if (huffman->value == '0') {
    		if (huffman->left->value == '0') {
    			fprintf(stream, "    %d -> %d [label=\"0\", color=green] \n %d [label = \" \", fillcolor=blue] \n %d[label = \" \", fillcolor=blue];\n",
    				huffman->idx, huffman->left->idx, huffman->idx, huffman->left->idx);
    		} else {
    			fprintf(stream, "    %d -> %d [label=\"0\", color=green] \n %d [label = \" \", fillcolor=blue] \n %d[label = \"%c\"];\n",
    				huffman->idx, huffman->left->idx, huffman->idx, huffman->left->idx, huffman->left->value);
    		}
    	} else {
    		if (huffman->left->value == '0') {
    			fprintf(stream, "    %d -> %d [label=\"0\", color=green]  \n %d [label = \"%c\"] \n %d[label = \"\", fillcolor=blue];\n",
    				huffman->idx, huffman->left->idx, huffman->idx, huffman->value, huffman->left->idx);
    		} else {
    			fprintf(stream, "    %d -> %d [label=\"0\", color=green]  \n %d [label = \"%c\"] \n %d[label = \"%c\"];\n",
    				huffman->idx, huffman->left->idx, huffman->idx, huffman->value, huffman->left->idx, huffman->left->value);
    		}
    	}
        
        drawHuffmanAux(huffman->left, stream);
    }
    if (huffman->right) {
        if (huffman->value == '0') {
    		if (huffman->right->value == '0') {
    			fprintf(stream, "    %d -> %d [label=\"1\", color=purple] \n %d [label = \" \", fillcolor=blue] \n %d[label = \" \", fillcolor=blue];\n",
    				huffman->idx, huffman->right->idx, huffman->idx, huffman->right->idx);
    		} else {
    			fprintf(stream, "    %d -> %d [label=\"1\", color=purple] \n %d [label = \" \", fillcolor=blue] \n %d[label = \"%c\"];\n",
    				huffman->idx, huffman->right->idx, huffman->idx, huffman->right->idx, huffman->right->value);
    		}
    	} else {
    		if (huffman->right->value == '0') {
    			fprintf(stream, "    %d -> %d [label=\"1\", color=purple] \n %d [label = \"%c\"] \n %d[label = \"\", fillcolor=blue];\n",
    				huffman->idx, huffman->right->idx, huffman->idx, huffman->value, huffman->right->idx);
    		} else {
    			fprintf(stream, "    %d -> %d [label=\"1\", color=purple] \n %d [label = \"%c\"] \n %d[label = \"%c\"];\n",
    				huffman->idx, huffman->right->idx, huffman->idx, huffman->value, huffman->right->idx, huffman->right->value);
    		}
    	}
        drawHuffmanAux(huffman->right, stream);
    }
}

void drawHuffman(TreeNode huffman, char *fileName) {
	FILE* stream = fopen("test.dot", "w");
	char buffer[SIZE];
    fprintf(stream, "digraph HEAP {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
    if (!huffman)
        fprintf(stream, "\n");
    else if (huffman->left == NULL && huffman->right == NULL)
        fprintf(stream, "    %lf;\n", huffman->frequency);
    else
        drawHuffmanAux(huffman, stream);
    fprintf(stream, "}\n");
    fclose(stream);
    sprintf(buffer, "dot test.dot | neato -n -Tpng -o %s", fileName);
	system(buffer);
}

int main() {
    char s[200];
	TreeNode huffman = createHuffmanTree("ana_are_mere");
    drawHuffman(huffman, "huffman1.png");
    strcpy(s, compress(huffman, "ana_are_mere"));
    printf("%s\n\n", s);
    printf("%s\n", decompress(huffman, s));
	huffman = freeTree(huffman);

	huffman = createHuffmanTree("ala_bala_portocala");
    drawHuffman(huffman, "huffman2.png");
    strcpy(s, compress(huffman, "ala_bala_portocala"));
    printf("%s\n\n", s);
    printf("%s\n\n", decompress(huffman, s));
	huffman = freeTree(huffman);

	huffman = createHuffmanTree("this_is_an_example_of_a_huffman_tree");
    drawHuffman(huffman, "huffman3.png");
    strcpy(s, compress(huffman, "this_is_an_example_of_a_huffman_tree"));
    printf("%s\n\n", s);
    printf("%s\n\n", decompress(huffman, s));
	huffman = freeTree(huffman);

	huffman = createHuffmanTree("aaaaaabbbbcccddef");
    drawHuffman(huffman, "huffman4.png");
    strcpy(s, compress(huffman, "aaaaaabbbbcccddef"));
    printf("%s\n\n", s);
    printf("%s\n\n", decompress(huffman, s));
	huffman = freeTree(huffman);
	return 0;
}