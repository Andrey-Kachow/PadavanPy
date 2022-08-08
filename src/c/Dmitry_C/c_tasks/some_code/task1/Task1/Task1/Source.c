#pragma warning( disable : 6386 )
#pragma warning( disable : 6387 )
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int SourceFunction(char* in_fileName, char** buffer) {
	FILE* ptrFile = fopen(in_fileName, "rb");

	if (ptrFile == NULL) {
		printf_s("*** ERROR: File error. ***\n");
		exit(1);
	}

	fseek(ptrFile, 0, SEEK_END);
	long lSize = ftell(ptrFile);
	rewind(ptrFile);

	*buffer = (char*) malloc(sizeof(char) * lSize);
	if (*buffer == NULL) {
		fputs("*** ERROR: Memory error. ***\n", stderr);
		exit(2);
	}

	size_t result = 0;
	


	printf_s("Result: %d\n", result);
	if (result != lSize) {
		fputs("*** ERROR: Read error. ***\n", stderr);
		exit(3);
	}

	fclose(ptrFile);

	return lSize;
}

int main(int argc, char **argv) {
	char* in_fileName = argv[1];
	char* out_fileName = argv[2];
	char* subString = argv[3];
	char* repString = argv[4];
	char* String = { 0 };

	if (argc != 5) {
		printf_s("*** ERROR: Invalid number of command line parameters. ***\n");
		printf_s("Example: Task1.exe input.txt output.txt 123 abc\n");
		return 0;
	}

	int lSize = SourceFunction(in_fileName, &String);
	printf_s("lSize: %d\n", lSize);
	printf_s("STRING: ");
	for (int i = 0; i < lSize; i++)
		printf_s("%c", String[i]);
	printf_s("\n");

	return 0;
}