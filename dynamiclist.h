#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

typedef struct DynamicList {
    void** items;
    int size, item_size;
} DynamicList;


DynamicList* createDynamicList(int item_size);

void clearDynamicList(DynamicList* list);

void freeDynamicList(DynamicList* list);

int getIndexDynamicList(DynamicList* list, void* item);

void addItemDynamicList(DynamicList* list, void* item);

void shiftItemsDynamicList(DynamicList* list, int index, int shift_amount);

void removeItemsDynamicList(DynamicList* list, int index, int remove_amount);



#endif // !DYNAMICLIST_H