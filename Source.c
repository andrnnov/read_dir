#include <stdio.h>
#include <windows.h>
#include <locale.h>

#include "header.h"

int main() {
    unsigned int num = 0;
    wchar_t path[100] = L" ";
    int type_sort;

    setlocale(LC_ALL, "Russian");
    
    do {
        printf("enter path or exit: ");
 //       for (sLen = 0; (ch = getwchar()) != '\n'; sLen++)
 //           path[sLen] = ch;
 //       path[sLen] = '\0';
        wscanf_s(L"%s", path, (unsigned)_countof(path));
        if (wcsncmp(path, L"exit", (unsigned)_countof(path))) {
            printf("1. Select sort. Sort by ascending size.\n");
            printf("2. Select sort. Sort by dicending size.\n");
            printf("3. Insert sort. Sort by ascending size.\n");
            printf("4. Insert sort. Sort by dicending size.\n");
            printf("5. Merge sort. Sort by ascending size.\n");
            printf("6. Merge sort. Sort by dicending size.\n");
            printf("7. Merge recursion sort. Sort by ascending size.\n");
            printf("8. Merge recursion sort. Sort by dicending size.\n");

            printf("Enter file sort type: ");
            scanf_s("%d", &type_sort);
            num = count_files(path);
            if (num < 0) continue;
            printf("\n");
            find(path, num, type_sort);
        }
    } while (wcsncmp(path, L"exit", (unsigned)sizeof(path)));

    return 1;
}