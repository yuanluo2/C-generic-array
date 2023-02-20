#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Array(type)       \
	struct {              \
		type* data;       \
		size_t capacity;  \
		size_t length;    \
	}                     

#define array_init(type, arr, isOOM)                                    \
	do{                                                                 \
		(arr).capacity = 5;                                             \
		(arr).length = 0;                                               \
		(arr).data = (type*)malloc(sizeof(type) * (arr).capacity);      \
																	    \
		(isOOM) = (arr).data == NULL ? 1 : 0;                           \
	}while(0)
		
#define array_destroy(arr)        \
	do{                           \
		if ((arr).data != NULL){  \
			free((arr).data);     \
		}                         \
								  \
		(arr).capacity = 0;       \
		(arr).length = 0;         \
	}while(0)
	
#define array_expand(type, arr, new_length, isOOM)                                 \
	do{                                                                            \
		if ((new_length) <= (arr).capacity){                                       \
			break;                                                                 \
		}                                                                          \
																				   \
		type* ptr = (type*)realloc((arr).data, new_length * sizeof(type));         \
		if (ptr == NULL){                                                          \
			(isOOM) = 1;                                                           \
			break;                                                                 \
		}                                                                          \
		else{                                                                      \
			(arr).data = ptr;                                                      \
			(arr).capacity = new_length;                                           \
		}                                                                          \
	}while(0)

#define array_add_back(type, arr, elem, isOOM)                           \
	do{                                                                  \
		if ((arr).length == (arr).capacity){                             \
			array_expand(type, (arr), 2 * (arr).capacity, (isOOM));      \
		}                                                                \
																		 \
		(arr).data[(arr).length] = (elem);                               \
		++(arr).length;                                                  \
	}while(0)

#define array_get(arr, index) \
	((arr).data + (index))

int main(){
	Array(int) arr;
	int isOOM = 0;
	
	array_init(int, arr, isOOM);
	
	int i;
	for (i = 0;i < 10;++i){
		array_add_back(int, arr, i, isOOM);
	}
	
	for (i = 0;i < 10;++i){
		printf("%d\n", *array_get(arr, i));
	}
	
	array_destroy(arr);
}
