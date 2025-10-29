# CircularBuffer - STL 호환 원형 버퍼 컨테이너

## 개요
고정 크기 원형 버퍼 `CircularBuffer<T>`를 구현한 STL 호환 컨테이너입니다. 센서 데이터 스트림과 같은 연속적인 데이터를 효율적으로 저장하고 처리할 수 있습니다.

## 주요 기능
- **템플릿 기반**: 모든 타입의 데이터 저장 가능
- **STL 호환**: STL 알고리즘과 함께 사용 가능
- **Forward Iterator 지원**: 범위 기반 for문 및 STL 알고리즘 사용 가능
- **효율적인 메모리 사용**: 고정 크기로 메모리 사용량 예측 가능
- **원형 버퍼 구조**: 용량 초과 시 가장 오래된 데이터를 자동으로 덮어씀

## 사용법

### 기본 사용 예제
```cpp
#include "CircularBuffer.h"

// double 타입의 원형 버퍼 생성 (용량 5)
CircularBuffer<double> buffer(5);

// 데이터 추가
buffer.push_back(1.0);
buffer.push_back(2.0);
buffer.push_back(3.0);

// 데이터 접근
double oldest = buffer.front();  // 가장 오래된 데이터
double newest = buffer.back();   // 가장 최근 데이터

// 범위 기반 for문으로 순회 (가장 오래된 것부터)
for (const auto& value : buffer) {
    std::cout << value << " ";
}
```

### STL 알고리즘과 함께 사용
```cpp
// 최대값 찾기
auto max_val = *std::max_element(buffer.begin(), buffer.end());

// 평균값 계산
double sum = std::accumulate(buffer.begin(), buffer.end(), 0.0);
double avg = sum / buffer.size();
```

## API 레퍼런스

### 생성자
- `CircularBuffer(size_t capacity)`: 지정된 용량으로 버퍼 생성

### 용량 및 크기 메서드
- `size_t capacity() const`: 버퍼의 최대 용량 반환
- `size_t size() const`: 현재 저장된 데이터 개수 반환
- `bool empty() const`: 버퍼가 비어있는지 확인

### 데이터 조작 메서드
- `void push_back(const T& item)`: 버퍼 끝에 데이터 추가
- `void pop_front()`: 가장 오래된 데이터 제거
- `T& front()`: 가장 오래된 데이터 참조 반환
- `T& back()`: 가장 최근 데이터 참조 반환

### 반복자
- `iterator begin()` / `const_iterator begin() const`: 시작 반복자
- `iterator end()` / `const_iterator end() const`: 끝 반복자
- `const_iterator cbegin() const`: const 시작 반복자
- `const_iterator cend() const`: const 끝 반복자

## 빌드 방법

### Windows (MinGW)
```cmd
g++ -std=c++14 -Wall -Wextra -O2 -o circular_buffer_test main.cpp
```

### Linux/macOS
```bash
make
```

## 실행 결과 예시
```
버퍼 내용 (가장 오래된 것부터): [24.1, 23.8, 25.2, 24.7, 26.1]
begin()부터 순회 시: 24.1, 23.8, 25.2, 24.7, 26.1 (가장 오래된 것부터)

tempBuffer.size() = 5
tempBuffer.capacity() = 5
tempBuffer.empty() = false
maxTemp = 26.1
avgTemp = 24.78
tempBuffer.front() = 24.1 // 가장 오래된 데이터
tempBuffer.back() = 26.1 // 가장 최근 데이터
```

## 파일 구조
- `CircularBuffer.h`: 템플릿 클래스 선언 및 Iterator 정의
- `CircularBuffer.tpp`: 템플릿 메서드 구현
- `main.cpp`: 사용 예제 및 테스트 코드
- `Makefile`: 빌드 스크립트

## 특징
1. **원형 버퍼 동작**: 용량이 가득 찬 상태에서 새 데이터 추가 시 가장 오래된 데이터를 자동으로 덮어씀
2. **STL 호환성**: `std::max_element`, `std::accumulate` 등 STL 알고리즘과 호환
3. **메모리 효율성**: 동적 크기 조정 없이 고정된 메모리 사용
4. **타입 안전성**: 템플릿을 통한 컴파일 타임 타입 체크
