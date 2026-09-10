#include "telecom_a2.h"

/**
 * [archive.c]
 * Function: validateBinaryArchive
 * Purpose: Verify file validity by checking that the file exists and its total size in bytes is a non-zero
multiple of sizeof(LogEntry)
 * Parameters:
 *   - *binFilename (char): name of binary file where data is stored
 * Variables:
 *   -None.
 * Example: int validbin = validateBinaryArchive(char *binFilename);
 * Effects: None. 
 * Return: returns 1 if valid, if not valid returns 0
 */
int validateBinaryArchive(char *binFilename){
    
    FILE *fp = fopen(binFilename, "rb");

    if (fp == NULL){
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long byte = ftell(fp);

    if(byte <=0){
        fclose(fp);
        return 0;
    } 
    else if (byte % sizeof(LogEntry)!= 0){
        fclose(fp);
        return 0;
    }
    fclose(fp);
    
    return 1;
}

/**
 * [archive.c]
 * Function: restoreFromBinary
 * Purpose: Loads the entire data in the binary file (binFilename) into a dynamically allocated array
of LogEntry
 * Parameters:
 *   - *binFilename (char): name of binary file where data is stored
 *   -  count (int *): pointing to an int that counts log entries
 * Variables:
 *   -None
 * Example: LogEntry *bin_restored = restoreFromBinary((char*)binFilename, &count2);
 * Effects: None. 
 * Return: Struct of type LogEntry 'logs' that has been memory allocated 
 */
LogEntry* restoreFromBinary(char *binFilename, int *count){
    FILE *fp = fopen(binFilename, "rb");
    if (fp == NULL){
        *count = 0;
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    *count = (int)(size/sizeof(LogEntry));

    LogEntry *logs = malloc(sizeof(LogEntry)*(*count));
    
    if(logs == NULL){
        fclose(fp);
        *count = 0;
        return NULL;
    }
    fread(logs,sizeof(LogEntry),*count,fp);

    fclose(fp);
    return(logs);
}
