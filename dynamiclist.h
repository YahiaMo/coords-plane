#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

typedef struct DynamicList {
    void** items;
    int size, item_size;
} DynamicList;


DynamicList* createDynamicList(int item_size);

void clearDynamicList(DynamicList* list);

void freeDynamicList(DynamicList* list);

int getIndex(DynamicList* list, void* item);

void addItem(DynamicList* list, void* item);

void shiftItems(DynamicList* list, int index, int shift_amount);

void removeItems(DynamicList* list, int index, int remove_amount);



#endif // !DYNAMICLIST_H