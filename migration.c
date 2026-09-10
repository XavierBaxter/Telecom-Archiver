/**
 * [migration.c]
 * Function: loadFromCSV
 * Purpose: returns a dynamically allocated array of LogEntry retrieved from CSV file
 * Parameters:
 *   - *filename (char): name of file holding the CSV data
 *   - count (int *): pointing to an int that counts log entries
 * Variables:
 *   -char buffer[1024]: buffer is stored as a char of size 1024,
 *   -int line_count: counts the total lines in the CSV file (1 line is 1 record)
 * Example: LogEntry *logs = loadFromCSV((char*)network_file, &count);
 * Effects: None. 
 * Return: Struct of type LogEntry that has been memory allocated 
 */
#include "telecom_a2.h"

LogEntry* loadFromCSV(char *filename, int *count){

    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        *count = 0;
        return NULL;
    }

    char buffer[1024];
    int line_count = 0;

    while(fgets(buffer,sizeof(buffer), fp)!= NULL){
        line_count++;
    }

    *count = line_count;
    rewind(fp);
    
    LogEntry *logs = malloc(sizeof(LogEntry)*(*count));

    if(logs == NULL){
        fclose(fp);
        *count = 0;
        return NULL;
    }

    for(int i = 0; i < *count; i++){
        fscanf(fp, " %19[^,],%d,%f,%d,%d", logs[i].userID, &logs[i].duration, 
                                &logs[i].dataUsage, &logs[i].towerID, &logs[i].successCode);
    }

    fclose(fp);
    return logs;
}

/**
 * [migration.c]
 * Function: convertToBinary
 * Purpose: writes the dynamically allocated array in logs to a binary file by using fwrite
 * Parameters:
 *   - *binFilename (char): name of binary file where data is stored
 *   -  logs (LogEntry *): pointer to struct holding log entries
 *   - count (int): the number of log entries/lines 
 * Variables:
 *   -size (size_t): stores number of log entries  
 * Example: convertToBinary("logs.bin", logs, count);
 * Effects: None. 
 * Return: None
 */
void convertToBinary(char *binFilename, LogEntry *logs, int count){

    FILE *fp = fopen(binFilename, "wb");

    if (fp == NULL){
        exit(1);
    }

    size_t size = fwrite(logs, sizeof(LogEntry), count, fp);

    if(size != (size_t)count){
        fclose(fp);
        exit(1);
    }

    fclose(fp);
}

/**
 * [migration.c]
 * Function: freeArchive
 * Purpose: releases all dynamically allocated memory on the heap
 * Parameters:
 *   - *logs (LogEntry **): pointers pointer referencing the struct logs
 *   -  logs (LogEntry *): pointer to struct holding log entries
 *   - count (int): the number of log entries/lines 
 * Variables:
 *   -None  
 * Example: freeArchive(&logs);
 * Effects: None. 
 * Return: None
 */
void freeArchive(LogEntry **logs){
    if(!logs){
        return;
    }
        
    free(*logs);
    *logs = NULL;
}
