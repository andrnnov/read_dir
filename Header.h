#pragma once
typedef struct {
    wchar_t name_file[260];
    unsigned long long size_file;
} file;

#define ASCENDING   1
#define DISCENDING  2

int merge_recursion_sort(unsigned long long* ptr_size, unsigned int start, unsigned int end, int type);
int merge_recursion(file* ptr, unsigned int count, int type);
int merge_sort(file* ptr, unsigned int count, int type);
int insert_sort(file* ptr, unsigned int count, int type);
int select_sort(file* ptr, unsigned int count, int type);
int find(wchar_t* PathAndName, unsigned int count, int type_sort);
int count_files(wchar_t* PathAndName);
void show_files(file* ptr, unsigned long long* buff, unsigned int count);
void menu(file* ptrf, unsigned int count, int type_sort);