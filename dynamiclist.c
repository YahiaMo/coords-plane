#include "dynamiclist.h"
#include <stdio.h>
#include <stdlib.h>


// Creates a new DynamicList that stores items of the given size
DynamicList* createDynamicList(int item_size){
    DynamicList* list = malloc(sizeof(DynamicList));
    list->size = 0;
    list->items = NULL;
    list->item_size = item_size;
    return list;
}


// Clears all items from the the list and frees their memory (but not the DynamicList itself)
void clearDynamicList(DynamicList* list){
    int i;
    for (i = 0; i < list->size; i++){
        free(list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->size = 0;
}


// Frees the memory of the DynamicList along with all items
void freeDynamicList(DynamicList* list){
    clearDynamicList(list);
    free(list);
}


// Returns the index of the given item inside the given DynamicList
int getIndexDynamicList(DynamicList* list, void* item){
    int i;
    for (i = 0; i < list->size; i++){
        if (list->items[i] == item){
            return i;
        }
    }
    return -1;
}


// Adds the given item to the end of the given DynamicList
void addItemDynamicList(DynamicList* list, void* item){
    list->size++;
    if (list->items == NULL){
        list->items = malloc(list->item_size);
    }
    else {
        list->items = realloc(list->items, list->size * list->item_size);
    }
    list->items[list->size - 1] = item;
}


void shiftItemsDynamicList(DynamicList* list, int index, int shift_amount){
    int i;
    for (i = index; i < list->size - shift_amount; i++){
        list->items[i] = list->items[i + shift_amount];
    }
}


// Removes the specified number items starting at the given index from the given DynamicList
void removeItemsDynamicList(DynamicList* list, int index, int remove_amount){
    int i;
    for (i = index; i < index + remove_amount; i++){
        free(list->items[i]);
    }
    shiftItemsDynamicList(list, index, remove_amount);
    list->size -= remove_amount;
    list->items = realloc(list->items, list->size * list->item_size);
}
