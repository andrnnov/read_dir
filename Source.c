#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <tchar.h>

void find(wchar_t* PathAndName)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    LONGLONG nFileLen = 0;

    setlocale(LC_ALL, "Russian");
    hf = FindFirstFile(PathAndName, &FindFileData);
    if (hf != INVALID_HANDLE_VALUE) {
        while (FindNextFile(hf, &FindFileData)) {
            nFileLen = (FindFileData.nFileSizeHigh * (MAXDWORD + 1)) + FindFileData.nFileSizeLow;
 //           printf("%ls\t %llu", FindFileData.cFileName, nFileLen);
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                printf("%ls\t Каталог\n", FindFileData.cFileName);
            else
                printf("%ls\t %llu\n", FindFileData.cFileName, nFileLen);
        }
        FindClose(hf);
        system("pause");
    }
}

int main() {
    find(_T("C:\\book\\*.*"));
    system("pause");
    return 0;
}