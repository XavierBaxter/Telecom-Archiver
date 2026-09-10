#ifndef TELECOM_A2_H
#define TELECOM_A2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 20
#define MAX_BUFFER_LEN 100
// #define MAX_LOGS 1000


// LogEntry struct
typedef struct {
    char userID[MAX_ID_LEN];  // Format: "UID-XXXX"
    int duration;        	  // In seconds
    float dataUsage;     	  // In Megabytes
    int towerID;         	  // Integer identifier
    int successCode;     	  // 1 = Success, 0 = Failed
} LogEntry;

// Singly Linked List Node
typedef struct LogNode {
    LogEntry data;
    struct LogNode *next;
} LogNode;

LogEntry* loadFromCSV(char *filename, int *count);
/* Returns a dynamically allocated array of LogEntry from the CSV data in filename.
Updates count with the number of LogEntry in the CSV file.
If the file doesn't exist or can't be opened, return NULL and set *count to 0.
If the file is empty, set *count to 0.
*/

void convertToBinary(char *binFilename, LogEntry *logs, int count);
/* Writes the entire dynamic array values in logs to a binary file (binFilename) using
exactly one fwrite call. Partial writes result in a zero mark for this function.
*/

void freeArchive(LogEntry **logs);
/* Safely releases all dynamically allocated memory on the heap.
After freeing, set *logs to NULL.
*/

int validateBinaryArchive(char *binFilename);
// The function must return 1 if the file is valid and return 0 if invalid.

LogEntry* restoreFromBinary(char *binFilename, int *count);
// Loads the entire data in the binary file (binFilename) 
// into a dynamically allocated array of LogEntry.
// If the file doesn't exist or can't be opened, return NULL and set *count to 0.

float recursiveTotalUsage(LogEntry *logs, int recordCount);
// sums the dataUsage of all LogEntry in logs. 
// recordCount is the total number of LogEntry in logs.

float recursiveMaxUsage(LogEntry *logs, int recordCount);
// returns the largest dataUsage value in non-empty logs.
// recordCount is the total number of LogEntry in logs.

// Linked List (linked_list.c)
LogNode* buildLogListFromBinary(char *binFilename);
// reads all records in the binary file binFilename 
// into a linked list of LogNode and returns a pointer 
// to the dynamically allocated linked list.

int countDroppedCalls(LogNode *head, int towerID);
// counts the number of dropped calls on the tower towerID
// when successCode == 0.

void removeUserLogs(LogNode **head, char *targetUID);
// removes all LogNodes belonging to the user whose userID is targetID. 
// If all nodes are removed and the list becomes empty, *head must be set to NULL.

void destroyLogList(LogNode **head);
// frees all dynamically allocated memory associated with the linked list.
// After freeing all nodes, set *head to NULL.

#endif
