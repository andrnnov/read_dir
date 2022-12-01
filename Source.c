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

int merge_sort(file* ptr, unsigned int count, int type) {
    unsigned int step = 1;              // ��� ��������� ������������������
    unsigned long long* buff, * temp;   // �������������� �������
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
        unsigned int index = 0;             // ������ ��������������� �������
        unsigned int l = 0;                 // ����� ������� �������
        unsigned int m = l + step;          // �������� �������
        unsigned int r = l + step * 2;      // ������ ������� �������
        do
        {
            m = m < count ? m : count;      // ����������� ������� �� ������� �� ������� ������������������
            r = r < count ? r : count;
            unsigned int i1 = l, i2 = m;    // ������� ������������ ���������
            while (i1 < m && i2 < r) {      // ���� i1 �� ����� �� �������� � i2 �� ����� �� �����
                switch (type) {
                case 1:
                    if (buff[i1] < buff[i2]) temp[index++] = buff[i1++];    // ��������� ������� �������������� ������������������
                    else temp[index++] = buff[i2++];
                    break;
                case 2:
                    if (buff[i1] > buff[i2]) temp[index++] = buff[i1++];    // ��������� ������� �������������� ������������������
                    else temp[index++] = buff[i2++];
                    break;
                }               
            }
            // ��� i1 < m ��� i2 < r - ������ ���� �� ���������� while ����� �����������
            while (i1 < m) temp[index++] = buff[i1++];  // ������� ���������� �������� ����������� ��������
            while (i2 < r) temp[index++] = buff[i2++];  // � �������������� ������
            l += step * 2;                              // ������������ �� ��������� ����������� �������
            m += step * 2;
            r += step * 2;
        } while (l < count);                            // ���� ����� ������� ������������ ������� - � �������� �����������������
        for (unsigned int i = 0; i < count; i++)        // ��������� �������������� ������ ������� � buff
            buff[i] = temp[i];
        step *= 2;                                      // ����������� � 2 ���� ��� ���������
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


int insert_sort(file* ptr, unsigned int count, int type) {
    unsigned int j = 0, key = 0;
    unsigned long long t = 0;
    unsigned long long* buff;
    double time_spent = 0.0;

    if ((buff = malloc(sizeof(unsigned long long) * count)) == NULL) {
        printf("Unable to allocate %llu bytes of memory for character buffer\n", count * sizeof(file));
        return 0;
    }
    for (unsigned int i = 0; i < count; i++) {
//        if (buff[i]) 
            buff[i] = ptr[i].size_file;
//            printf("buff[%d]=%llu\n", i, buff[i]);
    }

    clock_t begin = clock();
    for (unsigned int i = 0; i < count - 1; i++)
    {
        key = i + 1;
        t = buff[key];
        for (j = i + 1; j > 0; j--)
        {
            switch (type) {
            case 1:
                if (t > buff[j - 1])
                {
                    buff[j] = buff[j - 1];
                    key = j - 1;
                }
                break;
            case 2:
                if (t < buff[j - 1])
                {
                    buff[j] = buff[j - 1];
                    key = j - 1;
                }
                break;
            }
        }
        buff[key] = t;
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

int select_sort(file* ptr, unsigned int count, int type) {
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
        switch(type) {
        case 1:
            for (b = a + 1; b < count; ++b) {
                if (buff[b] < t) {
                    c = b;
                    t = buff[b];
                    exchange = 1;
                }
            }
            break;
        case 2:
            for (b = a + 1; b < count; ++b) {
                if (buff[b] > t) {
                    c = b;
                    t = buff[b];
                    exchange = 1;
                }
            }
            break;
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

int find(wchar_t* PathAndName, unsigned int count, int type_sort)
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
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
//                printf("%ls\t �������\n", FindFileData.cFileName);
            else {
                wcscpy_s(ptrf[i].name_file, sizeof(FindFileData.cFileName) / sizeof(wchar_t), FindFileData.cFileName);
 //               printf("sizeof() = %llu\n", (unsigned long long)(sizeof(FindFileData.cFileName) / sizeof(wchar_t)));
                if (i < count)
                    ptrf[i].size_file = nFileLen;
//                printf("\n%d\t%ls\t %llu\n", i, ptrf[i].name_file, ptrf[i].size_file);
                i++;
            }
        }
        switch(type_sort) {
        case 1: printf("Select sort. Sort by ascending size.\n");
                select_sort(ptrf, count, 1);
                break;
        case 2: printf("Select sort. Sort by dicending size.\n");
                select_sort(ptrf, count, 2);
                break;
        case 3: printf("Insert sort. Sort by ascending size.\n");
                insert_sort(ptrf, count, 1);
                break;
        case 4: printf("Insert sort. Sort by dicending size.\n");
                insert_sort(ptrf, count, 2);
                break;
        case 5: printf("Merge sort. Sort by ascending size.\n");
                merge_sort(ptrf, count, 1);
                break;
        case 6: printf("Merge sort. Sort by dicending size.\n");
                merge_sort(ptrf, count, 2);
                break;
        default:for (unsigned int j = 0; j < count; j++)
                    printf("%d\t%ls\t %llu\n", j, ptrf[j].name_file, ptrf[j].size_file);
                printf("Sort type from 1 to 6\n");
        }
//        merge_sort(ptrf, count);
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

wchar_t* doubles(wchar_t* s, wchar_t c) {   // ��������� � ������ s ������ c
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
    int type_sort;

    setlocale(LC_ALL, "Russian");
    
     do {
        printf("enter path or quit to exit: ");
//        fgetws(str, 100, stdin);
        wscanf_s(L"%s", path, (unsigned)_countof(path));
//        wprintf(L"\t%s\t%llu\n", doubles(path, ch), _countof(path));

        if (wcsncmp(path, L"quit", (unsigned)sizeof(path))) {
            printf("1. Select sort. Sort by ascending size.\n");
            printf("2. Select sort. Sort by dicending size.\n");
            printf("3. Insert sort. Sort by ascending size.\n");
            printf("4. Insert sort. Sort by dicending size.\n");
            printf("5. Merge sort. Sort by ascending size.\n");
            printf("6. Merge sort. Sort by dicending size.\n");
            printf("Enter file sort type: ");
            scanf_s("%d", &type_sort);
            num = count_files(path);
            printf("\n");
            find(path, num, type_sort);
        }
    } while (wcsncmp(path, L"quit", (unsigned)sizeof(path)));

//    wprintf_s(L"%ls", path);
//    num = count_files(path);
//    printf("num = %d\n", num);
//    find(path, num);
    return 1;
}