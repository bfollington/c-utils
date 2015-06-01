//
//  circular_list.h
//  c-utils
//
//  Created by Ben Follington on 1/06/2015.
//  Copyright (c) 2015 Ben Follington. All rights reserved.
//

#ifndef c_utils_circular_list_h
#define c_utils_circular_list_h

typedef unsigned int list_uint;
typedef uint8_t item_type;

typedef struct {
    list_uint start_index;
    list_uint end_index;
    list_uint length;
    item_type *data;
} circular_list;

void init_circular_list(circular_list *list, list_uint length);
bool list_append(circular_list *list, item_type item);
bool list_prepend(circular_list *list, item_type item);
item_type list_remove_from_start(circular_list *list);
item_type list_remove(circular_list *list);
list_uint list_length(circular_list *list);
item_type list_get(circular_list *list, list_uint index);
void list_expand(circular_list *list);
void destroy_circular_list(circular_list *list);

#endif
