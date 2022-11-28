#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
//#include <tchar.h>
#include <malloc.h>

typedef struct {
    wchar_t name_file[261];
    unsigned long long size_file;
} file;

int find(wchar_t* PathAndName, unsigned int count)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    unsigned long long nFileLen = 0;
    file *ptrf;
    int i = 0;
 
    ptrf = (file *)malloc((count) * sizeof(file));
    if (ptrf == NULL)
        return 0;
    hf = FindFirstFile(PathAndName, &FindFileData);
    if (hf != INVALID_HANDLE_VALUE) {
        while (FindNextFile(hf, &FindFileData)) {
            nFileLen = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                printf("%ls\t Каталог\n", FindFileData.cFileName);
            else {
                wcscpy_s(ptrf[i].name_file, sizeof(FindFileData.cFileName) / sizeof(wchar_t), FindFileData.cFileName);
 //               printf("sizeof() = %llu\n", (unsigned long long)(sizeof(FindFileData.cFileName) / sizeof(wchar_t)));
                ptrf[i].size_file = nFileLen;
//                printf("\n%d\t%ls\t %llu\n", i, ptrf[i].name_file, ptrf[i].size_file);
                i++;
            }
        }
        for(unsigned int j = 0; j < count; j++)
            printf("\n%d\t%ls\t %llu\n", j, ptrf[j].name_file, ptrf[j].size_file);
        free(ptrf);
        FindClose(hf);
        system("pause");
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


int main() {
    unsigned int num = 0;
    wchar_t *path = L"C:\\book\\*.*";

    setlocale(LC_ALL, "Russian");

//    wprintf_s(L"%ls", path);
    num = count_files(path);
    printf("num = %d\n", num);
    find(path, num);
//    system("pause");
    return 0;
}