#ifndef LOGFILEMANAGER_H
#define LOGFILEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

class LogFileManager {
public:
    // 기본 생성자
    LogFileManager() = default;
    
    // 소멸자
    ~LogFileManager();
    
    // 복사 생성자와 복사 대입 연산자 삭제 (RAII 원칙)
    LogFileManager(const LogFileManager&) = delete;
    LogFileManager& operator=(const LogFileManager&) = delete;
    
    // 이동 생성자와 이동 대입 연산자
    LogFileManager(LogFileManager&& other) noexcept;
    LogFileManager& operator=(LogFileManager&& other) noexcept;
    
    // 로그 파일 열기
    void openLogFile(const std::string& filename);
    
    // 로그 메시지 작성 (타임스탬프 자동 추가)
    void writeLog(const std::string& filename, const std::string& message);
    
    // 로그 읽기 (전체 로그 반환)
    std::vector<std::string> readLogs(const std::string& filename) const;
    
    // 로그 파일 닫기
    void closeLogFile(const std::string& filename);
    
    // 모든 로그 파일 닫기
    void closeAllLogFiles();
    
    // 활성 로그 파일 개수 반환
    size_t getActiveFileCount() const;

private:
    // 스마트 포인터로 파일 핸들 관리
    std::map<std::string, std::unique_ptr<std::ofstream>> logFiles;
    
    // 현재 타임스탬프 생성 함수
    std::string getCurrentTimestamp() const;
    
    // 파일 존재 여부 확인
    bool fileExists(const std::string& filename) const;
    
    // 로그 파일 유효성 검사
    void validateLogFile(const std::string& filename) const;
};

#endif // LOGFILEMANAGER_H
