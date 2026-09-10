#include "telecom_a2.h"


int main(void) {
    const char *network_file = "network_logs.csv";
    const char *binFilename = "logs.bin";
    int count = 0;

    LogEntry *logs = loadFromCSV((char*)network_file, &count);
    // Task 1: Initial Data Load
    if (logs == NULL || count <= 0) {
        fprintf(stderr, "Error: Could not load logs or file is empty.\n");
        return 1;
    }
    //Writes the dynamic array values in logs to a binary file
    convertToBinary((char*)binFilename, logs, count);
    printf("converted csv file to binary: %s\n", binFilename);

    //Verify file validity 
    int validbin = validateBinaryArchive((char*)binFilename);
    printf("loading valid binary data: %d\n", validbin);

    //releases all dynamically allocated memory on the heap
    freeArchive(&logs);

    //binary restoration
    int count2 = 0;
    LogEntry *bin_restored = restoreFromBinary((char*)binFilename, &count2);
    if (bin_restored == NULL || count2 <= 0) {
        fprintf(stderr, "Error: Could not load logs or file is empty.\n");
        freeArchive(&logs);
        freeArchive(&bin_restored);
        return 1;
    }

    printf("Restored %d records\n", count2);

    //sum the dataUsage of all LogEntry in logs, then return the largest dataUsage value in non-empty logs
    float total = recursiveTotalUsage(bin_restored, count2);
    float max = recursiveMaxUsage(bin_restored, count2);

    //printing recursive results out
    printf("the total data Usage is: %0.2f\n", total);
    printf("the largest data Usage is: %0.2f\n", max);

    //task 4:
    LogNode *head = buildLogListFromBinary((char*)binFilename);
    if (head != NULL) {
        
        removeUserLogs(&head, "UID-2001");
        int current_Tower = 1;
        //Counts the number of dropped calls on the tower
        int dropped_calls = countDroppedCalls(head, current_Tower);
        
        printf("the dropped calls on the current tower # %d, is %d\n", current_Tower, dropped_calls);
        
        //Free all dynamically allocated memory associated with the linked list head
        destroyLogList(&head);
    }

    //Release all dynamically allocated memory on the heap
    freeArchive(&logs);
    freeArchive(&bin_restored);

    //successful end message
    printf("Memory freed. Exiting.\n");
    return 0;
}
