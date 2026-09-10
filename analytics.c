#include "telecom_a2.h"
#include <stdlib.h>
#include <stdio.h>

float recursiveTotalUsage(LogEntry *logs, int recordCount){

    if(recordCount <= 0){
        return 0.0f;
    }
    return recursiveTotalUsage(logs+1, recordCount-1) + logs[0].dataUsage;
}

float recursiveMaxUsage(LogEntry *logs, int recordCount){
       if(recordCount <= 0){
        return 0.0f;
    }
    
    float maxUsage = recursiveMaxUsage(logs+1, recordCount-1);
    if(logs[0].dataUsage > maxUsage){
        return logs[0].dataUsage;
    }
    return maxUsage;
}