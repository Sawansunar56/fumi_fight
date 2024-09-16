#include "event_things.h"

void push_events(Arena *arena, event_list *list, event *v)
{
    event_node *node = PushArray(arena, 1, event_node);
    MemoryCopyStruct(&node->v, v);
    DLLPushFront(list->first, list->last, node);
    list->count++;
}

void pop_events(event_list *list, event_node *node) 
{
    DLLRemove(list->first, list->last, node);
    list->count++;
}
