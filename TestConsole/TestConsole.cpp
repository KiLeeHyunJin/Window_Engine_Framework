// TestConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <windows.h>

#include <fcntl.h>
#include <io.h>

 std::vector<std::wstring> getFilesInDirectory(const std::wstring& path) {
    std::vector<std::wstring> fileList;
    std::wstring searchPath = path + L"\\*";  // 모든 파일과 폴더 검색

    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::wstring name = findFileData.cFileName;

            // "." 및 ".." 제외
            if (name == L"." || name == L"..") {
                continue;
            }

            // 파일인지 확인 (디렉터리는 제외)
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                fileList.push_back(name);
            }

        } while (FindNextFileW(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    else {
        std::wcerr << L"Failed to open directory: " << path << std::endl;
    }
    return fileList;
}


std::wstring getCurrentDirectory() {
    wchar_t buffer[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, buffer);
    return std::wstring(buffer);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int prevCode = _setmode(_fileno(stdout), _O_U16TEXT);


    std::wcout << L"Current Directory: " << getCurrentDirectory() << std::endl;


    std::wstring path = L".";  // 현재 디렉터리
    std::vector<std::wstring> files = getFilesInDirectory(path);

    for (const auto& file : files) {
        std::wcout << file.c_str() << std::endl;
    }

    return 1;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
