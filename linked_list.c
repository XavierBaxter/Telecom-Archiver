/**
 * [linked_list.c]
 * Function: buildLogListFromBinary
 * Purpose: The program reads all records in the binary file binFilename into a linked list of LogNode
and returns a pointer to the dynamically allocated linked list.
 * Parameters:
 *   - *binFilename (char): name of binary file where data is stored
 * Variables:
 *   - head (LogNode *): Pointer to the linked list
     - LogEntry temp: temporary variable that reads the LogEntry from bin file
     - size: initialized as a long to store the size of the binary File (accessed through ftell)
     - count: total records/lines in the bin file
 * Example: LogNode *head = buildLogListFromBinary((char*)binFilename)
 * Effects: None. 
 * Return: Struct of type LogNode that has been memory allocated 
 */
#include "telecom_a2.h"

LogNode* buildLogListFromBinary(char *binFilename){

    FILE *fp = fopen(binFilename, "rb");
    if (fp == NULL){
        return NULL;
    }

    LogNode *head = NULL;
    LogEntry temp;

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    int count = (int)(size/sizeof(LogEntry));

    for(int i = 0; i < count; i++){

        if(fread(&temp, sizeof(LogEntry), 1, fp) != 1){
            break;
        }

        LogNode *newNode = malloc(sizeof(LogNode));

        if(newNode == NULL){
            destroyLogList(&head);
            fclose(fp);
            return NULL;

        }

        newNode->data = temp;
        newNode->next = NULL;

        if (head == NULL){
            head = newNode;
        }
        else{
            LogNode *current = head;

            while(current->next != NULL){
                current = current->next;
            }
            current->next = newNode;
        }
    }

    fclose(fp);
    return head;
}

/**
 * [linked_list.c]
 * Function: countDroppedCalls
 * Purpose: counts the number of dropped calls on the tower towerID when successCode == 0.
 * Parameters:
 *   - head (LogNode *): pointer to struct type LogNode
 *   - towerID (int): the number of log entries/lines 
 * Variables:
     - count (int): total records/lines in the bin file
 * Example: int dropped_calls = countDroppedCalls(head, current_Tower);
 * Effects: None. 
 * Return: total dropped calls as an int 
 */
int countDroppedCalls(LogNode *head, int towerID){
    
    if (head == NULL){
        return 0;
    }

    int count = 0;

    if(head->data.towerID == towerID && head->data.successCode == 0){
        count++;
    }
    return count+countDroppedCalls(head->next, towerID);
}


/**
 * [linked_list.c]
 * Function: removeUserLogs
 * Purpose: Removes all LogNodes belonging to the user whose userID is targetID
 * Parameters:
 *   - head (LogNode **): pointers pointer to struct type LogNode
 *   - targetUID (char *): the target ID we are removing from logs 
 * Variables:
 *   - temp (LogNode *): pointer used to temporarily access values in Node
 * Example: removeUserLogs(&head, "UID-2014");
 * Effects: None. 
 * Return: None. 
 */
void removeUserLogs(LogNode **head, char *targetUID){

    if (*head == NULL || targetUID == NULL){
        return;
    }

    if (strcmp((*head)->data.userID, targetUID) == 0){

        LogNode *temp = *head;
        *head = (*head)->next;
        free(temp);
        
        removeUserLogs(head, targetUID);
        return;
    }

    removeUserLogs(&(*head)->next, targetUID);
}

/**
 * [linked_list.c]
 * Function: destroyLogList
 * Purpose: Removes all LogNodes belonging to the user whose userID is targetID
 * Parameters:
 *   - head (LogNode **): pointers pointer to struct type LogNode
 * Variables:
 *   - currentNode (LogNode *): pointer used to temporarily access values in Node
 * Example: destroyLogList(&head);
 * Effects: Goes through each node in the list and sets to NULL 
 * Return: None. 
 */
void destroyLogList(LogNode **head){

    if (head == NULL){
        return;
    }

    LogNode *currentNode = *head;

    while (currentNode) {
        LogNode *tempNode = currentNode;
        currentNode = currentNode->next;
        free(tempNode);
    }
    
    *head = NULL;
}
