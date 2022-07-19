#include "huffcode.h"

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
	printf("Frequency table of Huffman tree:\n");
	for (size_t i=0;i<n-1;i++) {
		printf("| %c | %d | ", arr[i], freq[i]);
		printUp(root, array, top, arr[i]);
		printf("\n");
	}
	return 0;
}
