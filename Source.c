#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
//#include <tchar.h>

typedef struct {
    wchar_t name_file[260];
    unsigned long long size_file;
} file;

int merge_sort(file* ptr, unsigned int count) {
    unsigned int step = 1;              // шаг разбиения последовательности
    unsigned long long* buff, * temp;   // дополнительные массивы
    double time_spent = 0.0;

    if ((buff = malloc(sizeof(unsigned long long) * count)) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (buff[i])
            buff[i] = ptr[i].size_file;
    }
    if ((temp = malloc(sizeof(unsigned long long) * count)) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }

    clock_t begin = clock();
    while (step < count) {
        unsigned int index = 0;             // индекс результирующего массива
        unsigned int l = 0;                 // левая граница участка
        unsigned int m = l + step;          // середина участка
        unsigned int r = l + step * 2;      // правая граница участка
        do
        {
            m = m < count ? m : count;      // сортируемый участок не выходит за границы последовательности
            r = r < count ? r : count;
            unsigned int i1 = l, i2 = m;    // индексы сравниваемых элементов
            while (i1 < m && i2 < r) {                                  // пока i1 не дошёл до середины и i2 не дошёл до конца
                if (buff[i1] < buff[i2]) temp[index++] = buff[i1++];    // заполняем участок результирующей последовательности
                else temp[index++] = buff[i2++]; 
            }
            // Или i1 < m или i2 < r - только один из операторов while может выполниться
            while (i1 < m) temp[index++] = buff[i1++];  // заносим оставшиеся элементы сортируемых участков
            while (i2 < r) temp[index++] = buff[i2++];  // в результирующий массив
            l += step * 2;                              // перемещаемся на следующий сортируемый участок
            m += step * 2;
            r += step * 2;
        } while (l < count);                            // пока левая граница сортируемого участка - в пределах последоватльности
        for (unsigned int i = 0; i < count; i++)        // переносим сформированный массив обратно в buff
            buff[i] = temp[i];
        step *= 2;                                      // увеличиваем в 2 раза шаг разбиения
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
    printf("\n");

    for (unsigned int i = 0; i < count; i++)
        for (unsigned int j = 0; j < count; j++)
            if (buff[i] == ptr[j].size_file) {
                printf("%d\t%ls\t %llu\n", i, ptr[j].name_file, ptr[j].size_file);
                break;
            }

    free(temp);
    free(buff);
    return 1;
}


int insert_sort(file* ptr, unsigned int count) {
    unsigned int j;
    unsigned long long t = 0;
    unsigned long long* buff;
    double time_spent = 0.0;

    if ((buff = malloc(sizeof(unsigned long long) * count)) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (buff[i]) 
            buff[i] = ptr[i].size_file;
    }

    clock_t begin = clock();
    for (unsigned int i = 1; i < count; i++)
    {
        t = buff[i];
        j = i - 1;
        while (j >= 0 && buff[j] > t) {
            buff[j + 1] = buff[j];
            j--;
        }
        buff[j + 1] = t;
    }

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
    printf("\n");
//    for (unsigned int i = 0; i < count; i++)
//        printf("%llu\n", buff[i]);
    for (unsigned int i = 0; i < count; i++)
        for (j = 0; j < count; j++)
            if (buff[i] == ptr[j].size_file) {
                printf("%d\t%ls\t %llu\n", i, ptr[j].name_file, ptr[j].size_file);
                break;
            }
            
    free(buff);
    return 1;
}

int select_sort(file* ptr, unsigned int count) {
    unsigned int a, b, c;
    int exchange = 0;
    unsigned long long t = 0;
    unsigned long long* buff;
    double time_spent = 0.0;

    if ((buff = malloc(sizeof(unsigned long long) * count)) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (buff[i]) 
            buff[i] = ptr[i].size_file;
    }

    clock_t begin = clock();
    for (a = 0; a < count - 1; ++a) {
        exchange = 0;
        c = a;
        t = buff[a];
        for (b = a + 1; b < count; ++b) {
            if (buff[b] < t) {
                c = b;
                t = buff[b];
                exchange = 1;
            }
        }
        if (exchange) {
            buff[c] = buff[a];
            buff[a] = t;
        }
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

    printf("\n");
    for (a = 0; a < count; a++) 
        for (b = 0; b < count; b++) 
            if (buff[a] == ptr[b].size_file) {
                printf("%d\t%ls\t %llu\n", a, ptr[b].name_file, ptr[b].size_file);
                break;
            }
//        if (i < count)
//            printf("%llu\n", buff[i]);
    
    free(buff);
    return 1;
}

int find(wchar_t* PathAndName, unsigned int count)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    unsigned long long nFileLen = 0;
    file *ptrf;
    unsigned int i = 0;
 
    if ((ptrf = (file*)malloc((count) * (unsigned int)sizeof(file))) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }
    hf = FindFirstFile(PathAndName, &FindFileData);
    if (hf != INVALID_HANDLE_VALUE) {
        while (FindNextFile(hf, &FindFileData)) {
            nFileLen = (FindFileData.nFileSizeHigh * ((unsigned long long)MAXDWORD + 1)) + FindFileData.nFileSizeLow;
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                printf("%ls\t Каталог\n", FindFileData.cFileName);
            else {
                wcscpy_s(ptrf[i].name_file, sizeof(FindFileData.cFileName) / sizeof(wchar_t), FindFileData.cFileName);
 //               printf("sizeof() = %llu\n", (unsigned long long)(sizeof(FindFileData.cFileName) / sizeof(wchar_t)));
                if (i < count)
                    ptrf[i].size_file = nFileLen;
//                printf("\n%d\t%ls\t %llu\n", i, ptrf[i].name_file, ptrf[i].size_file);
                i++;
            }
        }
        for(unsigned int j = 0; j < count; j++)
            printf("%d\t%ls\t %llu\n", j, ptrf[j].name_file, ptrf[j].size_file);
        merge_sort(ptrf, count);
//        select_sort(ptrf, count);
//        insert_sort(ptrf, count);
        free(ptrf);
        FindClose(hf);
//        printf("%d\n", (unsigned int)sizeof(file));
        system("pause");
    }
    else {
        printf("INVALID HANDLE VALUE!!!\n");
        return 0;
    }
    return 1;
}

int count_files(wchar_t* PathAndName)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    int i = 0;

    hf = FindFirstFile(PathAndName, &FindFileData);
    if (hf != INVALID_HANDLE_VALUE) 
        while (FindNextFile(hf, &FindFileData)) 
            if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) i++;

    FindClose(hf);
//    system("pause");
    return i;
}

wchar_t* doubles(wchar_t* s, wchar_t c) {   // удваивает в строке s символ c
    int cnt = 0;
    for (const wchar_t* t = s; *t; ++t)
        if (*t == c) ++cnt;
    wchar_t * q = s + wcslen(s) - 1,
        * t = s + wcslen(s) + cnt;
    *t-- = 0;
    while (q >= s)
    {
        if (*q == c) *t-- = c;
        *t-- = *q--;
    }
    return s;
}

int main() {
    unsigned int num = 0;
//    wchar_t *path = L"C:\\book\\*.*";
    wchar_t path[100];
    wchar_t ch = '\\';

    setlocale(LC_ALL, "Russian");
    
    while (wcsncmp(path, L"quit", (unsigned)sizeof(path))) {
        printf("enter path or quit to exit: ");
//        fgetws(str, 100, stdin);
        wscanf_s(L"%s", path, (unsigned)_countof(path));
        wprintf(L"\t%s\t%llu\n", doubles(path, ch), _countof(path));
        if (wcsncmp(path, L"quit", (unsigned)sizeof(path))) {
            num = count_files(path);
            printf("num = %d\n", num);
            find(path, num);
        }
    }

//    wprintf_s(L"%ls", path);
//    num = count_files(path);
//    printf("num = %d\n", num);
//    find(path, num);
    return 1;
}