#include<string.h>
#include<stdlib.h>

unsigned long hash_function(unsigned char* str) {
    unsigned long hash = 5381;
    int c;
    while(c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

template <typename T> struct HMValues {
    char* key;
    T value;
};

template <typename T> struct HashMap{
    HMValues<T>** vals;
    int count;
    int size;
};

template <typename T> HMValues<T>* create_value(char* key, T val) {
    HMValues<T>* newVal = (HMValues<T>*) malloc(sizeof(HMValues<T>));
    newVal->key = (char*) malloc(strlen(key) + 1);
    strcpy(newVal->key, key);
    newVal->value = val;
    return newVal;
}

template <typename T> HashMap<T>* create_table(int size){
    HashMap<T>* newHM = (HashMap<T>*) malloc(sizeof(HashMap<T>));
    newHM->size = size;
    newHM->count = 0;
    newHM->vals = (HMValues<T>**) calloc(newHM->size, sizeof(HMValues<T>*));
    for(int i = 0;i<newHM->size;i++) {
        newHM->vals[i] = NULL;
    } 
    return newHM;
}

template <typename T> void free_val(HMValues<T>* val) {
    free(val->key);
    free(val->value);
    free(val);
}

template <typename T> void free_HM(HashMap<T>* HM) {
    for(int i = 0;i<HM->size;i++) {
        if(HM->vals[i] != NULL) free(HM->vals[i]);
    }
    free(HM->vals);
    free(HM);
}

template <typename T> void HM_insert(HashMap<T>* HM, char* key, T val) {
    HMValues<T>* newVal = create_value<T>(key, val);

    int index = hash_function(key)%HM->size;

    HMValues<T>* curr = HM->vals[index];

    if(curr == NULL) {
        if(HM->count == HM->size) {
            printf("Error!!! HashMap is full\n");
            free(newVal);
            return;
        }
        HM->vals[index] = newVal;
        HM->count++;
    }
    else{
        if(strcmp(curr->key, key) == 0) {
        }
        else{
            
        }
    }
}