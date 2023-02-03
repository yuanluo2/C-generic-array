#include <stdio.h>
#include "array.h"

void test_array_int(){
	ARRAY_TEMPLATE(int);
	
	Status status;
	Array_int arr;
	Array_int_init(&arr, &status);
	if (status == STATUS_OUT_OF_MEMORY){
		printf("out of memory.\n");
		return;
	}
	
	int i;
	for (i = 0;i < 9;++i){
		Array_int_add_back(&arr, i * i, &status);
	}
	
	int* elem;
	for (i = 0;i < arr.length;++i){
		elem = Array_int_at(&arr, i);
		printf("%d\n", *elem);
	}
	
	free(arr.data);
}

void test_array_string(){
	typedef char* string;
	ARRAY_TEMPLATE(string);
	
	Status status;
	Array_string arr;
	
	Array_string_init(&arr, &status);
	if (status == STATUS_OUT_OF_MEMORY){
		printf("out of memory.\n");
		return;
	}
	
	Array_string_add_back(&arr, "This", &status);
	Array_string_add_back(&arr, "is", &status);
	Array_string_add_back(&arr, "just", &status);
	Array_string_add_back(&arr, "for", &status);
	Array_string_add_back(&arr, "test", &status);
	Array_string_add_back(&arr, "array", &status);
	
	string* elem;
	int i;
	for (i = 0;i < arr.length;++i){
		elem = Array_string_at(&arr, i);
		printf("%s\n", *elem);
	}
	
	free(arr.data);
}

typedef struct Object{
	int num;
} Object;

typedef Object* Objptr;

void test_array_object(){
	ARRAY_TEMPLATE(Objptr);
	
	Status status;
	Array_Objptr arr;
	
	Array_Objptr_init(&arr, &status);
	if (status == STATUS_OUT_OF_MEMORY){
		printf("out of memory.\n");
		return;
	}
	
	int i;
	for (i = 0;i < 9;++i){
		Object* obj = (Object*)malloc(sizeof(Object));
		obj->num = i * i;
		Array_Objptr_add_back(&arr, obj, &status);
	}
	
	Objptr* elem_ptr;
	for (i = 0;i < arr.length;++i){
		elem_ptr = Array_Objptr_at(&arr, i);
		printf("%d\n", (*elem_ptr)->num);
	}
	
	for (i = 0;i < arr.length;++i){
		elem_ptr = Array_Objptr_at(&arr, i);
		free(*elem_ptr);
	}
	
	free(arr.data);
}

int main(){
	
}
