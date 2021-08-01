#include <stdio.h>
#include <stdlib.h>

#define SYS_ERR_FORM "system error: in %s(), calling %s() failed\n"
#define SYS_ERR(callee) sysErr(__func__, (callee))

#define OUT_NAME "binot.h"
#define SG_NAME "BINOT_H"

#define CHAR_0 "00000000"

static void sysErr(const char *caller, const char *callee)
{
	fprintf(stderr, SYS_ERR_FORM, caller, callee);
	exit(EXIT_FAILURE);
}

static void clearFile(char *fileName)
{
	FILE *file = fopen(fileName, "w");
	if (!file) SYS_ERR("fopen");
	fprintf(file, "");
}

static FILE *openFileToWrite(char *fileName)
{
	FILE *file = fopen(fileName, "w");
	if (!file) SYS_ERR("fopen");
	return file;
}

static void writeGuardStart(FILE *outFile)
{
	fprintf(outFile, "#ifndef %s\n", SG_NAME);
	fprintf(outFile, "#define %s\n", SG_NAME);
	fprintf(outFile, "\n");
}

static void writeGuardEnd(FILE *outFile)
{
	fprintf(outFile, "#endif //%s\n", SG_NAME);
}

static void incrementCharBits(char *charBits)
{
	for (char i = 7; i >= 0; --i)
	{
		if (charBits[i] == '0')
		{
			charBits[i] = '1';
			return;
		}
		charBits[i] = '0';
	}
}

static void writeBasicMacros(FILE *outFile)
{
	char charBits[] = CHAR_0;
	for (int i = 0; i < 256; ++i)
	{
		fprintf(outFile, "#define b%s 0x%xu\n", charBits, i);
		incrementCharBits(charBits);
	}
	fprintf(outFile, "\n");
}

static void writeFunctionLikeMacros(FILE *outFile)
{
	int i = 1
}

static void createBinot(void)
{
	clearFile(OUT_NAME);
	FILE *outFile = openFileToWrite(OUT_NAME);
	writeGuardStart(outFile);
	writeBasicMacros(outFile);
	writeGuardEnd(outFile);
}

int main()
{
	createBinot();
	return 0;
}
