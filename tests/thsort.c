/*
 * thsort.c - word list sorting routine
 * Created: 26 Nov 1998
 * Author: Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#include <thai/thcoll.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* for qsort() */
typedef int (*CMPFUNC)(const void *, const void *);

static size_t readData(FILE *dataFile, thchar_t *data[], int maxData)
{
    size_t nData = 0;
    static char wordBuf[128];

    while (nData < maxData && fgets(wordBuf, sizeof wordBuf, dataFile) != NULL)
    {
        int len = strlen(wordBuf);
        if (len == 0) { return nData; }
        /* eliminate terminating '\n' */
        wordBuf[--len] = 0;

        /* allocate & copy the line */
        data[nData] = (thchar_t*)malloc(len+1);
        if (data[nData] == NULL) {
            printf("Warning: Only %d items were read\n", nData);
            return nData;
        }
        strcpy((char*)data[nData], wordBuf);
        nData++;
    }

    return nData;
}

static void freeData(thchar_t *data[], size_t nItems)
{
    size_t i;

    for (i=0; i<nItems; i++) {
        free(data[i]);
    }
}

static int dataCmp(const thchar_t **pStr1, const thchar_t **pStr2)
{
    return th_strcoll(*pStr1, *pStr2);
}

static void sortData(thchar_t *data[], size_t nItems)
{
    qsort(data, nItems, sizeof data[0], (CMPFUNC)dataCmp);
}

static void writeData(FILE *outFile, thchar_t *data[], size_t nItems)
{
    size_t  i;

    for (i = nItems; i > 0; i--) {
        fprintf(outFile, "%s\n", *data);
        data++;
    }
}

#define MAX_DATA  40000
static thchar_t *data[MAX_DATA];

int main(int argc, char *argv[])
{
    FILE   *dataFile;
    FILE   *outFile;
    size_t  dataRead;
    char    DataFileName[64];
    char    OutFileName[64];

    if (argc == 3) {
        strcpy(DataFileName, argv[1]);
        strcpy(OutFileName, argv[2]);
    } else {
        fprintf(stderr, "Usage: thsort <input file> <output file>\n");
        return 1;
    }

    dataFile = fopen(DataFileName, "rt");
    if (dataFile == NULL) {
        fprintf(stderr, "Can't open file %s\n", DataFileName);
        perror("fopen");
        return 1;
    }

    outFile = fopen(OutFileName, "wt");
    if (outFile == NULL) {
        fprintf(stderr, "Can't open file %s for write\n", OutFileName);
        perror("fopen");
        return 1;
    }

    dataRead = readData(dataFile, data, MAX_DATA);
    sortData(data, dataRead);
    writeData(outFile, data, dataRead);
    freeData(data, dataRead);

    fclose(outFile);
    fclose(dataFile);

    return 0;
}

