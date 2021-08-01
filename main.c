#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SYS_ERR_FORM "system error: in %s(), calling %s() failed\n"
#define SYS_ERR(callee) sysErr(__func__, (callee))

#define OUT_NAME "binot.h"
#define SG_NAME "BINOT_H"

#define CHAR_LEN CHAR_BIT
#define CHAR_0 '0'

static void sysErr(const char *caller, const char *callee)
{
	fprintf(stderr, SYS_ERR_FORM, caller, callee);
	exit(EXIT_FAILURE);
}

static void sysMsg(const char *msg)
{
	fprintf(stdout, "%s\n", msg);
}

static void clearFile(char *fileName)
{
	FILE *file = fopen(fileName, "w");
	if (!file) SYS_ERR("fopen");
	fprintf(file, "");
	sysMsg("blank file created");
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
	for (char i = CHAR_LEN - 1; i >= 0; --i)
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
	char charBits[CHAR_LEN + 1];
	for (int i = 0; i < CHAR_LEN; ++i)
	{
		charBits[i] = CHAR_0;
	}
	charBits[CHAR_LEN] = '\0';
	for (int i = 0; i < UCHAR_MAX; ++i)
	{
		fprintf(outFile, "#define b%s 0x%xu\n", charBits, i);
		incrementCharBits(charBits);
	}
	fprintf(outFile, "\n");
}

static void writeFunctionLikeMacros(FILE *outFile)
{
	int i = 1;
}

static void createBinot(void)
{
	sysMsg("STARTING binary notation header creator...");
	clearFile(OUT_NAME);
	FILE *outFile = openFileToWrite(OUT_NAME);
	writeGuardStart(outFile);
	writeBasicMacros(outFile);
	writeGuardEnd(outFile);
	writeFunctionLikeMacros(outFile);
	sysMsg("header created successfully");
}

int main()
{
	createBinot();
	return 0;
}
