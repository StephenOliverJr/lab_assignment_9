#include <stdio.h>
#include <stdlib.h>
#define MAX_HASH_SIZE 100

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType *records;
	int size;
};

// Compute the hash function
int hash(int x, int size)
{
	return x % size;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i, j;
    struct RecordType *record;
    printf("Records in Hash:\n");
    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        if (pHashArray[i].records != NULL) // Check if the bucket is not empty
        {
            record = pHashArray[i].records;
            printf("%d %c %d", record->id, record->name, record->order);
            record = record->next;
            while (record != NULL) // Traverse the linked list
            {
                printf(" -> %d %c %d", record->id, record->name, record->order);
                record = record->next;
            }
        }
        printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType hashTable[MAX_HASH_SIZE];
    int i;
    for (i = 0; i < MAX_HASH_SIZE; i++)
    {
        hashTable[i].records = NULL;
        hashTable[i].size = 0;
    }

    // Insert records into the hash table
    for (i = 0; i < recordSz; i++)
    {
        int index = hash(pRecords[i].id, MAX_HASH_SIZE);
        struct RecordType *newRecord = (struct RecordType*)malloc(sizeof(struct RecordType));
        *newRecord = pRecords[i];
        newRecord->next = hashTable[index].records;
        hashTable[index].records = newRecord;
        hashTable[index].size++;
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, MAX_HASH_SIZE);

    // Free memory allocated for records
    for (i = 0; i < recordSz; i++)
    
    free(pRecords);

    return 0;
}