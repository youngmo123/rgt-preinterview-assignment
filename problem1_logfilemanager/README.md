# LogFileManager C++ 구현

## 프로젝트 개요
스마트 포인터를 활용한 리소스 관리 시스템으로, 다중 로그 파일을 안전하고 효율적으로 관리하는 C++ 클래스입니다.

## 주요 기능

### 1. 다중 로그 파일 관리
- 여러 로그 파일을 동시에 열고 관리
- 각 파일에 독립적으로 로그 기록
- 파일별 개별 제어 가능

### 2. 자동 타임스탬프
- 모든 로그 메시지에 자동으로 타임스탬프 추가
- 형식: `[YYYY-MM-DD HH:MM:SS] 메시지`

### 3. 스마트 포인터 기반 리소스 관리
- `std::unique_ptr<std::ofstream>`을 사용한 안전한 파일 핸들 관리
- RAII 원칙 준수로 자동 리소스 해제
- 메모리 누수 방지

### 4. 예외 안전성
- 파일 열기/쓰기/읽기 실패 시 적절한 예외 처리
- 강력한 예외 안전성 보장
- 사용자 친화적인 오류 메시지

### 5. 이동 의미론 지원
- 복사 생성자/대입 연산자 삭제 (리소스 중복 방지)
- 이동 생성자/대입 연산자 구현
- 효율적인 객체 전달

### 6. 자동 로그 파일 정리
- 테스트 시작 시 기존 로그 파일 자동 정리
- 매번 실행할 때마다 깨끗한 상태에서 시작
- 중복 로그 누적 방지

### 7. 스마트 메시지 출력 제어
- 이동 의미론 사용 시 중복 메시지 출력 방지
- 빈 객체의 소멸자에서는 불필요한 메시지 출력 안함
- 실제로 리소스를 가진 객체에서만 정리 메시지 출력

## 클래스 구조

```cpp
class LogFileManager {
public:
    // 생성자/소멸자
    LogFileManager() = default;
    ~LogFileManager();
    
    // 복사 방지, 이동 허용
    LogFileManager(const LogFileManager&) = delete;
    LogFileManager& operator=(const LogFileManager&) = delete;
    LogFileManager(LogFileManager&& other) noexcept;
    LogFileManager& operator=(LogFileManager&& other) noexcept;
    
    // 핵심 기능
    void openLogFile(const std::string& filename);
    void writeLog(const std::string& filename, const std::string& message);
    std::vector<std::string> readLogs(const std::string& filename) const;
    void closeLogFile(const std::string& filename);
    void closeAllLogFiles();
    size_t getActiveFileCount() const;

private:
    // 파일 관리
    std::map<std::string, std::unique_ptr<std::ofstream>> logFiles;
    
    // 유틸리티 함수
    std::string getCurrentTimestamp() const;
    bool fileExists(const std::string& filename) const;
    void validateLogFile(const std::string& filename) const;
};
```

## 사용 예시

```cpp
#include "LogFileManager.h"
#include <iostream>
#include <fstream>

int main() {
    // 테스트 전 기존 로그 파일 정리 (선택사항)
    std::remove("error.log");
    std::remove("debug.log");  
    std::remove("info.log");
    
    LogFileManager manager;
    
    // 로그 파일 열기
    manager.openLogFile("error.log");
    manager.openLogFile("debug.log");
    manager.openLogFile("info.log");
    
    // 로그 메시지 작성 (타임스탬프 자동 추가)
    manager.writeLog("error.log", "Database connection failed");
    manager.writeLog("debug.log", "User login attempt");
    manager.writeLog("info.log", "Server started successfully");
    
    // 로그 읽기
    std::vector<std::string> errorLogs = manager.readLogs("error.log");
    for (const auto& log : errorLogs) {
        std::cout << log << std::endl;
    }
    
    // 파일 닫기 (선택사항 - 소멸자에서 자동 처리)
    manager.closeLogFile("debug.log");
    
    return 0;
}
```

## 컴파일 및 실행

### 방법 1: Makefile 사용
```bash
# 컴파일
make

# 실행
make run

# 또는
make test

# 정리
make clean
```

### 방법 2: 직접 컴파일

**Windows 환경:**
```cmd
g++ -std=c++14 main.cpp LogFileManager.cpp -o test
.\test.exe
```

**Linux/Unix 환경:**
```bash
g++ -std=c++14 main.cpp LogFileManager.cpp -o test
./test
```

### 한글 인코딩 문제 해결 (Windows)
Windows에서 한글이 깨져 보일 경우, 실행 전에 다음 명령어를 입력하세요:
```cmd
chcp 65001
```

## 출력 예시

```
=== LogFileManager 테스트 프로그램 ===

기존 로그 파일 정리 완료

1. 로그 파일들 열기...
로그 파일 열림: error.log
로그 파일 열림: debug.log
로그 파일 열림: info.log
활성 파일 개수: 3

2. 로그 메시지 작성...
로그 메시지가 성공적으로 작성되었습니다.

3. 로그 읽기 테스트...
// error.log 파일 내용:
[2025-10-28 21:14:13] Database connection failed
[2025-10-28 21:14:13] Authentication service unavailable

// debug.log 파일 내용:
[2025-10-28 21:14:13] User login attempt
[2025-10-28 21:14:13] Processing user request

// info.log 파일 내용:
[2025-10-28 21:14:13] Server started successfully
[2025-10-28 21:14:13] Configuration loaded

4. 개별 파일 닫기 테스트...
로그 파일 닫힘: debug.log
debug.log 파일 닫힘 후 활성 파일 개수: 2

5. 예외 처리 테스트...
예상된 예외: 파일이 열려있지 않습니다: debug.log. 먼저 openLogFile()을 호출하세요.
예상된 예외: 파일이 존재하지 않습니다: nonexistent.log

6. 이동 의미론 테스트...
이동 후 manager2 활성 파일 개수: 2

=== 테스트 완료 ===
모든 로그 파일이 닫혔습니다.
```

## 기술적 특징

### 1. RAII (Resource Acquisition Is Initialization)
- 생성자에서 리소스 획득, 소멸자에서 자동 해제
- 예외 상황에서도 리소스 누수 방지

### 2. 스마트 포인터 활용
- `std::unique_ptr`로 독점적 소유권 관리
- 자동 메모리 관리로 안전성 향상

### 3. 예외 안전성
- Strong Exception Safety 보장
- 예외 발생 시 객체 상태 일관성 유지

### 4. 현대 C++ 기법
- C++14 표준 사용
- 이동 의미론 활용
- auto 키워드 및 범위 기반 for 루프

### 5. 향상된 사용자 경험
- 중복 메시지 출력 방지를 통한 깔끔한 로그
- 이동된 객체의 조용한 소멸 처리
- 명확하고 혼란 없는 상태 메시지

## 파일 구조
```
problem1_logfilemanager/
├── LogFileManager.h      # 클래스 선언
├── LogFileManager.cpp    # 클래스 구현 (중복 메시지 방지 개선)
├── main.cpp             # 테스트 프로그램 (로그 정리 기능 포함)
├── Makefile            # 빌드 스크립트
├── README.md           # 프로젝트 설명
├── test.exe            # 실행 파일 (Windows)
├── error.log           # 에러 로그 파일 (실행 후 생성)
├── debug.log           # 디버그 로그 파일 (실행 후 생성)
└── info.log            # 정보 로그 파일 (실행 후 생성)
```

### 주요 업데이트 사항
- **자동 로그 정리**: main.cpp에서 테스트 시작 시 기존 로그 파일 자동 삭제
- **크로스 플랫폼**: Windows/Linux 실행 명령어 구분 설명  
- **한글 지원**: Windows 환경에서 한글 인코딩 문제 해결 방법 추가
- **완전한 테스트**: 예외 처리와 이동 의미론까지 포함한 전체 테스트
- **중복 메시지 방지**: 이동 의미론 사용 시 빈 객체에서 불필요한 "모든 로그 파일이 닫혔습니다." 메시지 출력 방지
- **스마트 소멸자**: `closeAllLogFiles()`에서 빈 컨테이너 체크로 깔끔한 종료 메시지 제공

### 개발 과정에서 해결된 주요 이슈들
1. **한글 인코딩 문제**: Windows 콘솔에서 UTF-8 설정 (`chcp 65001`) 필요성 발견 및 해결
2. **로그 파일 누적 문제**: append 모드로 인한 중복 로그 누적 → 자동 정리 기능 추가
3. **중복 메시지 출력**: 이동 의미론 사용 시 두 객체에서 동일 메시지 출력 → 조건부 메시지 출력으로 개선
4. **리소스 관리 최적화**: RAII와 스마트 포인터를 통한 완전 자동화된 리소스 해제
