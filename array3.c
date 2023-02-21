#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>

typedef struct array{
	void* data;
	size_t length;
	size_t capacity;
	size_t elemSize;
} array_t;

/*
	arr: Must not be NULL.
	elemSize: Specify the single data length, just like sizeof(int).
	return arr if success, else return NULL.
*/
array_t* arrayInit(array_t* arr, size_t elemSize);

/*
	arr: Must not be NULL.
*/
void arrayFree(array_t* arr);

/*
	arr: Must not be NULL.
	newCapacity: make sure newCapacity > arr->capacity
	return arr if success, else return NULL.
*/
array_t* arrayExpand(array_t* arr, size_t newCapacity);

/*
	@param arr The pointer refers to a array_t object, arr must not be NULL.
	@param index
	returns a pointer to the element at the specified position.
*/
void* arrayGet(array_t* arr, size_t index);

/*
	arr: Must not be NULL.
	returns a pointer to the element at the last position.
*/
void* arrayAddBack(array_t* arr, const void* elem);

int main(){
	array_t arr;
	
	if (arrayInit(&arr, sizeof(int)) == NULL){
		perror("arrayInit()");
		return -1;
	}
	
	int i;
	for (i = 0;i < 13;++i){
		if (arrayAddBack(&arr, &i) == NULL){
			perror("arrayAddBack()");
			goto clean;
		}
	}
	
	for (i = 0;i < arr.length;++i){
		printf("%d\n", *(int*)arrayGet(&arr, i));
	}
	
	clean:
	arrayFree(&arr);
}

array_t* arrayInit(array_t* arr, size_t elemSize){
	arr->length = 0;
	arr->capacity = 5;
	arr->elemSize = elemSize;
	arr->data = malloc(arr->elemSize * arr->capacity);
	
	if (arr->data == NULL){
		errno = ENOMEM;
		arr->capacity = 0;
		arr->elemSize = 0;
		return NULL;
	}
	else{
		return arr;
	}
}

void arrayFree(array_t* arr){
	if (arr->data != NULL){
		free(arr->data);
	}
	
	arr->length = 0;
	arr->capacity = 0;
	arr->elemSize = 0;
}

array_t* arrayExpand(array_t* arr, size_t newCapacity){
	void* ptr = realloc(arr->data, newCapacity * arr->elemSize);
	
	if (ptr == NULL){
		errno = ENOMEM;
		return NULL;
	}
	
	arr->data = ptr;
	arr->capacity = newCapacity;
	return arr;
}

void* arrayGet(array_t* arr, size_t index){
	return (arr->data + index * arr->elemSize);
}

void* arrayAddBack(array_t* arr, const void* elem){
	if (arr->length == arr->capacity){
		if (arrayExpand(arr, 2 * arr->capacity) == NULL){
			return NULL;
		}
	}
	
	void* emptyPos = arrayGet(arr, arr->length);
	memcpy(emptyPos, elem, arr->elemSize);
	++(arr->length);
	return emptyPos;
}
