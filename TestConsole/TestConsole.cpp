﻿// TestConsole.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
class CustomVector {
private:
    std::vector<int> data;

public:
    // 데이터 추가
    void add(int value) 
    {
        data.push_back(value);

        int size = data.size();
    }

    // 특정 값을 삭제 (O(N))
    void remove(int value) 
    {
        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end()) 
        {
            data.erase(it);
        }
    }

    // 특정 값을 가장 뒤로 이동 (O(N))
    void moveToBack(int value) 
    {
        const int endIdx = data.size();
        if (endIdx <= 1)
        {
            return;
        }

        int currentIdx = value;

        auto iter = data.cbegin() + currentIdx;//std::find(data.cbegin(), data.cend(), currentIdx);
        if (iter != data.cend() && iter != data.cend() - 1)
        { // 마지막 요소면 이동 불필요
            int temp = *iter;
            data.erase(iter);               // 요소 삭제 (O(N))
            data.push_back(temp);          // 뒤에 추가 (O(1))
        }

        //for (int i = currentIdx; i < endIdx; i++)
        //{
        //    data[i]->SetUIIndex(i);
        //}
    }

    // 특정 값을 특정 위치로 이동 (O(N))
    void move(int value, size_t new_index) {
        if (new_index >= data.size()) return;

        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end()) {
            int temp = *it;
            data.erase(it);
            data.insert(data.begin() + new_index, temp);
        }
    }

    // 데이터 출력
    void display() const {
        for (int num : data) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    CustomVector arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);

    arr.display();  // 출력: 1 2 3 4 5

    arr.moveToBack(2);
    arr.display();  // 출력: 1 3 4 5 2

    arr.move(3, 0);
    arr.display();  // 출력: 3 1 4 5 2

    arr.remove(4);
    arr.display();  // 출력: 3 1 5 2 (4 삭제됨)

    return 0;
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
