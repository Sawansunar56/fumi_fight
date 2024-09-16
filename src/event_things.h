#pragma once
#include "types.h"
#include "arena.h"

enum event_type
{
    ET_PRESS,
    ET_RELEASE,
    ET_MOUSE_PRESS,
    ET_MOUSE_RELEASE,
    ET_COUNT
};

struct event 
{
    event_type Type;
};

struct event_node
{
    event_node* next;
    event_node* prev;
    event v;
};

struct event_list
{
    event_node* first;
    event_node* last;

    u64 count;
};

void push_events(Arena* arena, event_list* list, event *v);
void pop_events(event_list* list, event_node* node);
