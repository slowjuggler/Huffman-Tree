#ifndef HUFFCODE_H
#define HUFFCODE_H

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

struct RawDataNode* newNode(char data, unsigned freq);
struct RawData* createRawData(unsigned density);
void swapElements(struct RawDataNode** x, struct RawDataNode** y);
void DataIf(struct RawData* rawData, int aux);
struct RawDataNode* extractData(struct RawData* rawData);
void insertData(struct RawData* rawData, struct RawDataNode* rawDataNode);
void buildData(struct RawData* rawData);
struct RawData* BuildData(char data[], int freq[], int size);
struct RawDataNode* buildTree(char data[], int freq[], int size);
void printUp(struct RawDataNode* root, int arr[], int top, char symbol);

#endif //  HUFFCODE_H 


