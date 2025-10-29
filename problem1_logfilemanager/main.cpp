#include "LogFileManager.h"
#include <iostream>
#include <fstream>

int main() {
    try {
        std::cout << "=== LogFileManager 테스트 프로그램 ===" << std::endl;
        std::cout << std::endl;
        
        // 테스트 전 기존 로그 파일 정리
        std::remove("error.log");
        std::remove("debug.log");  
        std::remove("info.log");
        std::cout << "기존 로그 파일 정리 완료" << std::endl;
        std::cout << std::endl;
        
        // LogFileManager 객체 생성
        LogFileManager manager;
        
        std::cout << "1. 로그 파일들 열기..." << std::endl;
        // 여러 로그 파일 열기
        manager.openLogFile("error.log");
        manager.openLogFile("debug.log");
        manager.openLogFile("info.log");
        
        std::cout << "활성 파일 개수: " << manager.getActiveFileCount() << std::endl;
        std::cout << std::endl;
        
        std::cout << "2. 로그 메시지 작성..." << std::endl;
        // 각 파일에 로그 메시지 작성 (타임스탬프 자동 추가)
        manager.writeLog("error.log", "Database connection failed");
        manager.writeLog("debug.log", "User login attempt");
        manager.writeLog("info.log", "Server started successfully");
        
        // 추가 로그 메시지
        manager.writeLog("error.log", "Authentication service unavailable");
        manager.writeLog("debug.log", "Processing user request");
        manager.writeLog("info.log", "Configuration loaded");
        
        std::cout << "로그 메시지가 성공적으로 작성되었습니다." << std::endl;
        std::cout << std::endl;
        
        std::cout << "3. 로그 읽기 테스트..." << std::endl;
        // error.log 파일 읽기
        std::cout << "// error.log 파일 내용:" << std::endl;
        std::vector<std::string> errorLogs = manager.readLogs("error.log");
        for (const auto& log : errorLogs) {
            std::cout << log << std::endl;
        }
        std::cout << std::endl;
        
        // debug.log 파일 읽기
        std::cout << "// debug.log 파일 내용:" << std::endl;
        std::vector<std::string> debugLogs = manager.readLogs("debug.log");
        for (const auto& log : debugLogs) {
            std::cout << log << std::endl;
        }
        std::cout << std::endl;
        
        // info.log 파일 읽기
        std::cout << "// info.log 파일 내용:" << std::endl;
        std::vector<std::string> infoLogs = manager.readLogs("info.log");
        for (const auto& log : infoLogs) {
            std::cout << log << std::endl;
        }
        std::cout << std::endl;
        
        std::cout << "4. 개별 파일 닫기 테스트..." << std::endl;
        manager.closeLogFile("debug.log");
        std::cout << "debug.log 파일 닫힘 후 활성 파일 개수: " << manager.getActiveFileCount() << std::endl;
        std::cout << std::endl;
        
        std::cout << "5. 예외 처리 테스트..." << std::endl;
        try {
            // 닫힌 파일에 쓰기 시도
            manager.writeLog("debug.log", "This should fail");
        } catch (const std::exception& e) {
            std::cout << "예상된 예외: " << e.what() << std::endl;
        }
        
        try {
            // 존재하지 않는 파일 읽기 시도
            manager.readLogs("nonexistent.log");
        } catch (const std::exception& e) {
            std::cout << "예상된 예외: " << e.what() << std::endl;
        }
        std::cout << std::endl;
        
        std::cout << "6. 이동 의미론 테스트..." << std::endl;
        LogFileManager manager2 = std::move(manager);
        std::cout << "이동 후 manager2 활성 파일 개수: " << manager2.getActiveFileCount() << std::endl;
        std::cout << std::endl;
        
        std::cout << "=== 테스트 완료 ===" << std::endl;
        // 소멸자에서 자동으로 모든 파일이 닫힘
        
    } catch (const std::exception& e) {
        std::cerr << "오류 발생: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
