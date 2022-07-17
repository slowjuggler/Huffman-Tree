/* Huffman Tree
 * 
 * This is a code demonstrating the Huffman algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct RawDataNode { 
	char data;
	unsigned freq; 
	struct RawDataNode *left, *right;
};
	
struct RawData { 
	unsigned size;
	unsigned density;
	struct RawDataNode** array;
};
	
static unsigned int total = 0;
	
struct RawDataNode* newNode(char data, unsigned freq) {	
	struct RawDataNode* temp = (struct RawDataNode*)malloc(sizeof(struct RawDataNode));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}
	
struct RawData* createRawData(unsigned density) {
	struct RawData* rawData = (struct RawData*)malloc(sizeof(struct RawData));
	rawData->size = 0; 
	rawData->density = density; 
	rawData->array = (struct RawDataNode**)malloc(rawData->density * sizeof(struct RawDataNode*));   
	return rawData;
}
	
void swapElements(struct RawDataNode** x, struct RawDataNode** y) {
	struct RawDataNode* temp = *x;
	*x = *y;
	*y = temp;
}
	
void DataIf(struct RawData* rawData, int aux) {
	int lower = aux;
	int left = 2 * aux + 1;
	int right = 2 * aux + 2;
	if (left < rawData->size && rawData->array[left]->freq < rawData->array[lower]->freq) {
		lower = left;
	}
	if (right < rawData->size && rawData->array[right]->freq < rawData->array[lower]->freq) {
		lower = right;
	}
	if (lower != aux) {
		swapElements(&rawData->array[lower], &rawData->array[aux]);
		DataIf(rawData, lower);
	}
}
	
struct RawDataNode* extractData(struct RawData* rawData) {
	struct RawDataNode* temp = rawData->array[0];
	rawData->array[0] = rawData->array[rawData->size - 1];
	--rawData->size;
	DataIf(rawData, 0);
	return temp;
}
	
void insertData(struct RawData* rawData, struct RawDataNode* rawDataNode) {
	++rawData->size;
	int i = rawData->size - 1;
	while (i && rawDataNode->freq < rawData->array[(i - 1) / 2]->freq) {
		rawData->array[i] = rawData->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	rawData->array[i] = rawDataNode;
}
	
void buildData(struct RawData* rawData) {
	int n = rawData->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i) {
		DataIf(rawData, i);
	}
}
	
struct RawData* BuildData(char data[], int freq[], int size) {
	struct RawData* rawData = createRawData(size);
	for (int i = 0; i < size; ++i) {
		rawData->array[i] = newNode(data[i], freq[i]);
	}
	rawData->size = size;
	buildData(rawData);
	return rawData;
}
	
struct RawDataNode* buildTree(char data[], int freq[], int size) {
	struct RawDataNode *left, *right, *top;
	struct RawData* rawData = BuildData(data, freq, size);
	while (!(rawData->size == 1)) {
		left = extractData(rawData);
		right = extractData(rawData);
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertData(rawData, top);
	}
	return extractData(rawData);
}
	
	
void printUp(struct RawDataNode* root, int arr[], int top, char symbol) {
	if (root->left) {
		arr[top] = 0;
		printUp(root->left, arr, top + 1, symbol);
	}
	if (root->right) {
		arr[top] = 1;
		printUp(root->right, arr, top + 1, symbol);
	}
	if ((root->data) == symbol) {   
		for (size_t i = 0; i < top; ++i) {
			printf("%d", arr[i]);
		}
		printf(" ");
		total+=top;
	}
} 
	
	
int main() {	
	int array[256], top = 0;		
	char arr[256] = {0};
	int freq[256] = {0};
	char string[256] = {0};
	char temp[8] = {0};
	int flag, len, n = 1;
	printf("Enter data to encode:\n");
	scanf("%[^\n]s", string);
	if ((len = strlen(string)) == 0) {
		printf("Please try again...\n");	;
		exit(1);
	}
	printf("%d bits before encoding:\n", len*8);
	for (size_t i=0;i<len;i++) {
		for (size_t j=0;j<8;j++) {
			if (string[i] & (1 << j)) {
				temp[j] = 1;
			} else {
				temp[j] = 0;
			}
		}
		for (size_t j=0;j<8;j++) {
			printf("%d", temp[7-j]);
		}
		printf(" ");
	}
	printf("\n");
	for (size_t i=0;i<len;i++) {
		flag = 0;
		for (size_t j=0;j<n;j++) {
			if (arr[j] == string[i]) {				
				flag = 1;
			}		
		}
		if (flag == 0) {
			arr[n-1] = string[i];
			for (size_t j=0;j<len;j++) {
				if (arr[n-1] == string[j]) {
					freq[n-1]++;
				}
			}
			n++;
		}
	}
	struct RawDataNode* root = buildTree(arr, freq, n-1);
	printf("Encoded data:\n");
	for (size_t i=0;i<len;i++) {
		printUp(root, array, top, string[i]);
	}
	printf("\n");
	double comp = 100 - 100*total/(len*8);
	printf("Total: %d bits after encoding, %2.1f%% compressed\n", total, comp);
	printf("Frequency table of Huffman tree:\n");
	for (size_t i=0;i<n-1;i++) {
		printf("| %c | %d | ", arr[i], freq[i]);
		printUp(root, array, top, arr[i]);
		printf("\n");
	}
	return 0;
}
	
