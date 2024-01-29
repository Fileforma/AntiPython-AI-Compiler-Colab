#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#define TRUEBOOL 1
#define FALSEBOOL 0
size_t GetFileSize(char *fileName){FILE *fp = fopen(fileName, "rb");assert(fp != NULL);fseek(fp, 0L, SEEK_END);size_t currentFileSize = ftell(fp);rewind(fp);fclose(fp);return currentFileSize;}
char *GetSourceCode(size_t fileSize, char *fileName)
{
	int c = 0;
	char *result = calloc(fileSize, sizeof(char));
	FILE *fp = fopen(fileName, "r");assert(fp != NULL);
	size_t i = 0;	
	while((c = fgetc(fp)) != EOF){result[i] = c;i+=1;}
	assert(i == fileSize);
	fclose(fp);
	return result;
}
