#include "LogFileManager.h"

// 소멸자 - 모든 파일을 안전하게 닫음
LogFileManager::~LogFileManager() {
    closeAllLogFiles();
}

// 이동 생성자
LogFileManager::LogFileManager(LogFileManager&& other) noexcept
    : logFiles(std::move(other.logFiles)) {
}

// 이동 대입 연산자
LogFileManager& LogFileManager::operator=(LogFileManager&& other) noexcept {
    if (this != &other) {
        closeAllLogFiles(); // 기존 파일들 닫기
        logFiles = std::move(other.logFiles);
    }
    return *this;
}

// 로그 파일 열기
void LogFileManager::openLogFile(const std::string& filename) {
    if (filename.empty()) {
        throw std::invalid_argument("파일명이 비어있습니다.");
    }
    
    // 이미 열린 파일인지 확인
    if (logFiles.find(filename) != logFiles.end()) {
        std::cout << "경고: " << filename << " 파일이 이미 열려있습니다." << std::endl;
        return;
    }
    
    try {
        // 스마트 포인터로 파일 스트림 생성
        auto fileStream = std::make_unique<std::ofstream>(filename, std::ios::app);
        
        if (!fileStream->is_open()) {
            throw std::runtime_error("파일 열기 실패: " + filename);
        }
        
        // 파일이 성공적으로 열렸으면 맵에 추가
        logFiles[filename] = std::move(fileStream);
        
        std::cout << "로그 파일 열림: " << filename << std::endl;
        
    } catch (const std::exception& e) {
        throw std::runtime_error("로그 파일 열기 중 오류 발생: " + std::string(e.what()));
    }
}

// 로그 메시지 작성
void LogFileManager::writeLog(const std::string& filename, const std::string& message) {
    validateLogFile(filename);
    
    try {
        auto& fileStream = logFiles[filename];
        
        if (!fileStream->is_open()) {
            throw std::runtime_error("파일이 열려있지 않습니다: " + filename);
        }
        
        // 타임스탬프와 함께 로그 작성
        std::string logEntry = "[" + getCurrentTimestamp() + "] " + message;
        *fileStream << logEntry << std::endl;
        fileStream->flush(); // 즉시 파일에 쓰기
        
    } catch (const std::exception& e) {
        throw std::runtime_error("로그 작성 중 오류 발생: " + std::string(e.what()));
    }
}

// 로그 읽기
std::vector<std::string> LogFileManager::readLogs(const std::string& filename) const {
    std::vector<std::string> logs;
    
    if (!fileExists(filename)) {
        throw std::runtime_error("파일이 존재하지 않습니다: " + filename);
    }
    
    try {
        std::ifstream inputFile(filename);
        
        if (!inputFile.is_open()) {
            throw std::runtime_error("파일 읽기 실패: " + filename);
        }
        
        std::string line;
        while (std::getline(inputFile, line)) {
            logs.push_back(line);
        }
        
    } catch (const std::exception& e) {
        throw std::runtime_error("로그 읽기 중 오류 발생: " + std::string(e.what()));
    }
    
    return logs;
}

// 로그 파일 닫기
void LogFileManager::closeLogFile(const std::string& filename) {
    auto it = logFiles.find(filename);
    
    if (it != logFiles.end()) {
        if (it->second && it->second->is_open()) {
            it->second->close();
        }
        logFiles.erase(it);
        std::cout << "로그 파일 닫힘: " << filename << std::endl;
    } else {
        std::cout << "경고: " << filename << " 파일이 열려있지 않습니다." << std::endl;
    }
}

// 모든 로그 파일 닫기
void LogFileManager::closeAllLogFiles() {
    if (logFiles.empty()) {
        return; // 닫을 파일이 없으면 메시지 출력하지 않음
    }
    
    for (auto& pair : logFiles) {
        if (pair.second && pair.second->is_open()) {
            pair.second->close();
        }
    }
    logFiles.clear();
    std::cout << "모든 로그 파일이 닫혔습니다." << std::endl;
}

// 활성 로그 파일 개수 반환
size_t LogFileManager::getActiveFileCount() const {
    return logFiles.size();
}

// 현재 타임스탬프 생성 (private 메서드)
std::string LogFileManager::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}

// 파일 존재 여부 확인 (private 메서드)
bool LogFileManager::fileExists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}

// 로그 파일 유효성 검사 (private 메서드)
void LogFileManager::validateLogFile(const std::string& filename) const {
    if (filename.empty()) {
        throw std::invalid_argument("파일명이 비어있습니다.");
    }
    
    auto it = logFiles.find(filename);
    if (it == logFiles.end()) {
        throw std::runtime_error("파일이 열려있지 않습니다: " + filename + ". 먼저 openLogFile()을 호출하세요.");
    }
}
