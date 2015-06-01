//
//  circular_list.c
//  c-utils
//
//  Created by Ben Follington on 1/06/2015.
//  Copyright (c) 2015 Ben Follington. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circular_list.h"

void init_circular_list(circular_list *list, list_uint length) {
    list->data = malloc(length * sizeof(item_type));
    list->start_index = list->end_index = 0;
    list->length = length;
}

bool list_append(circular_list *list, item_type item) {
    
    list_uint new_end = list->end_index + 1;
    
    // Wrap the list if we go off the end
    if (new_end >= list->length) {
        new_end -= list->length;
    }
    
    // No room left in the list
    if (new_end == list->start_index) {
        list_expand(list);
        list_append(list, item);
        return true;
    }
    
    list->data[list->end_index] = item;
    list->end_index = new_end;
    return true;
}

bool list_prepend(circular_list *list, item_type item) {
    
    int new_start = list->start_index - 1;
    
    // Wrap the list if we go off the end
    if (new_start < 0) {
        new_start += list->length;
    }
    
    // No room left in the list
    if (new_start == list->end_index) {
        list_expand(list);
        list_prepend(list, item);
        return true;
    }
    
    list->data[new_start] = item;
    list->start_index = new_start;
    
    for (int i = 0; i < list->length; i++) {
        printf("%u,", list->data[i]);
    }
    printf("\n");
    return true;
}

item_type list_remove_from_start(circular_list *list) {
    int new_start = list->start_index + 1;
    
    if (new_start >= list->length) {
        new_start -= list->length;
    }
    
    item_type ret = list->data[list->start_index];
    list->start_index = new_start;
    return ret;
}

item_type list_remove(circular_list *list) {
    int new_end = list->end_index - 1;
    
    if (new_end < 0) {
        new_end += list->length;
    }
    
    item_type ret = list->data[new_end];
    list->end_index = new_end;
    return ret;
}

list_uint list_length(circular_list *list) {
    if (list->start_index <= list->end_index) {
        return list->end_index - list->start_index;
    } else {
        return list->length - (list->start_index - list->end_index);
    }
}

item_type list_get(circular_list *list, list_uint index) {
    
    list_uint n = list->start_index + index;
    
    if (n >= list->length) {
        n -= list->length;
    }
    
    //printf("Index: %u\n", n);
    return list->data[n];
}

void list_expand(circular_list *list) {
    list_uint new_length = list->length * 2;
    item_type *new_data = malloc(new_length * sizeof(item_type));
    list_uint old_length = list_length(list);
    
    item_type n;
    
    for (int i = 0; i < old_length; i++) {
        n = list_get(list, i);
        new_data[i] = n;
    }
    
    list->start_index = 0;
    list->end_index = old_length;
    list->length = new_length;
    free(list->data);
    list->data = new_data;
}


void destroy_circular_list(circular_list *list) {
    free(list->data);
}
