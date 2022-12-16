#pragma once
typedef struct {
    wchar_t name_file[260];
    unsigned long long size_file;
} file;

int merge_recursion_sort(unsigned long long* ptr_size, unsigned int start, unsigned int end, int type);
int merge_recursion(file* ptr, unsigned int count, int type);
int merge_sort(file* ptr, unsigned int count, int type);
int insert_sort(file* ptr, unsigned int count, int type);
int select_sort(file* ptr, unsigned int count, int type);
int find(wchar_t* PathAndName, unsigned int count, int type_sort);
int count_files(wchar_t* PathAndName);
