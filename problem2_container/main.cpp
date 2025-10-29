#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "CircularBuffer.h"

int main() {
    std::cout << std::fixed << std::setprecision(1);
    
    // 템플릿을 이용해 double 타입의 CircularBuffer 생성 (용량 5)
    CircularBuffer<double> tempBuffer(5);
    
    // 온도 데이터 추가 (더 많은 데이터를 추가해서 일부가 덮어써지도록)
    tempBuffer.push_back(23.5);
    tempBuffer.push_back(24.1);
    tempBuffer.push_back(23.8);
    tempBuffer.push_back(25.2);
    tempBuffer.push_back(24.7);
    tempBuffer.push_back(26.1);  // 이 값이 첫 번째 값(23.5)을 덮어씀
    
    // 버퍼 내용 출력 (가장 오래된 것부터)
    std::cout << "버퍼 내용 (가장 오래된 것부터): [";
    bool first = true;
    for (const auto& temp : tempBuffer) {
        if (!first) std::cout << ", ";
        std::cout << temp;
        first = false;
    }
    std::cout << "]" << std::endl;
    
    // 가장 오래된 데이터부터 순회 출력
    std::cout << "begin()부터 순회 시: ";
    first = true;
    for (auto it = tempBuffer.begin(); it != tempBuffer.end(); ++it) {
        if (!first) std::cout << ", ";
        std::cout << *it;
        first = false;
    }
    std::cout << " (가장 오래된 것부터)" << std::endl;
    
    // 기본 정보 출력
    std::cout << std::endl;
    std::cout << "tempBuffer.size() = " << tempBuffer.size() << std::endl;
    std::cout << "tempBuffer.capacity() = " << tempBuffer.capacity() << std::endl;
    std::cout << "tempBuffer.empty() = " << (tempBuffer.empty() ? "true" : "false") << std::endl;
    
    // STL 알고리즘 사용
    // 최대값 계산
    auto maxTemp = *std::max_element(tempBuffer.begin(), tempBuffer.end());
    std::cout << "maxTemp = " << maxTemp << std::endl;
    
    // 평균값 계산
    double sum = std::accumulate(tempBuffer.begin(), tempBuffer.end(), 0.0);
    double avgTemp = sum / tempBuffer.size();
    std::cout << std::setprecision(2) << "avgTemp = " << avgTemp << std::endl;
    
    // front()와 back() 테스트
    std::cout << std::setprecision(1);
    std::cout << "tempBuffer.front() = " << tempBuffer.front() << " // 가장 오래된 데이터" << std::endl;
    std::cout << "tempBuffer.back() = " << tempBuffer.back() << " // 가장 최근 데이터" << std::endl;
    
    // 범위 기반 for문 지원 확인
    std::cout << std::endl << "범위 기반 for문을 사용한 순회:" << std::endl;
    for (const auto& temp : tempBuffer) {
        std::cout << "온도: " << temp << "°C" << std::endl;
    }
    
    return 0;
}
