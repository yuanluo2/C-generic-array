#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef enum Status{
	STATUS_OK,
	STATUS_OUT_OF_MEMORY,
	STATUS_SUBSCRIPT_OUT_OF_INDEX,
	STATUS_UNKNOWN
} Status;

#define ARRAY_TEMPLATE(T)       \
	typedef struct Array_##T{   \
		T* data;                \
		size_t capacity;        \
		size_t length;          \
	} Array_##T;                \
							                                    \
	void Array_##T##_init(Array_##T* arr, Status* status){      \
		(arr)->capacity = 5;                                    \
		(arr)->length = 0;                                      \
		(arr)->data = (T*)malloc(sizeof(T) * (arr)->capacity);  \
											                    \
		if (NULL == (arr)->data){                               \
			*status = STATUS_OUT_OF_MEMORY;                     \
		}                                                       \
		else{									                \
			*status = STATUS_OK;                                \
		}                                                       \
	}                                                           \
	                                                    \
	T* Array_##T##_at(Array_##T* arr, size_t index){    \
		return &((arr)->data[index]);                   \
	}                                                   \
	                                                                        \
	T* Array_##T##_check_at(Array_##T* arr, size_t index, Status* status){  \
		if (index >= (arr)->length){                                        \
			*status = STATUS_SUBSCRIPT_OUT_OF_INDEX;                        \
			return NULL;                                                    \
		}                                                                   \
																			\
		return Array_##T##_at((arr), index);                                \
	}                                                                       \
	                                                                            \
	void Array_##T##_add_back(Array_##T* arr, T elem, Status* status){          \
		if ((arr)->length == (arr)->capacity){                                  \
			T* temp = (T*)realloc(arr->data, sizeof(T) * 2 * (arr)->capacity);  \
			if (NULL == temp){                                                  \
				*status = STATUS_OUT_OF_MEMORY;                                 \
				return;                                                         \
			}                                                                   \
																				\
			(arr)->data = temp;                                                 \
			(arr)->capacity *= 2;                                               \
		}                                                                       \
																				\
		((arr)->data)[((arr)->length)] = elem;                                  \
		++((arr)->length);                                                      \
		*status = STATUS_OK;                                                    \
	}
