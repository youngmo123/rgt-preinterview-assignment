# 🚀 RGT Problem Solutions

**Robot Global Team** 면접전 수행과제 

## 📋 프로젝트 개요

이 저장소는 RGT에서 제시한 4가지 프로그래밍 문제중 1번,2번,4번에 대한 해결책을 담고 있습니다. 각 문제는 서로 다른 기술 스택과 접근 방식을 요구하며, 실무에서 자주 사용되는 핵심 기술들을 다룹니다.

## 🛠️ 해결된 문제들

**노션 전체 페이지** : https://www.notion.so/RGT-2996a63aee9b8076a749c32f0796ba0d

### 1. 📁 [Problem 1: Log File Manager](./problem1_logfilemanager/)
- **언어**: C++
- **주요 기술**: 파일 I/O, 로그 레벨 관리, 예외 처리
- **핵심 기능**: 디버그/정보/에러 로그 분리 관리
- **노션 개별페이지**: https://www.notion.so/1_logfilemanager-29a6a63aee9b80d0803bc9f1df190188

### 2. 🔄 [Problem 2: Circular Buffer Container](./problem2_container/)
- **언어**: C++
- **주요 기술**: STL, 템플릿, Iterator 패턴
- **핵심 기능**: STL 호환 원형 버퍼 컨테이너 구현
- **노션 개별페이지**: https://www.notion.so/2-STL-29b6a63aee9b8062b5ccee75c934f5c9

### 4. 🌐 [Problem 4: RESTful API](./problem4_restfulapi/)
- **언어**: Python (FastAPI)
- **주요 기술**: REST API, SQLite, JWT 인증
- **핵심 기능**: 도서관 관리 시스템 API
- **노션 개별페이지**: https://www.notion.so/4-FastAPI-RESTful-API-2996a63aee9b806b9380cf3a94dd1151

## 🖥️ 개발 환경

- **운영체제**: Windows 11 (Build 26200)
- **IDE**: VSCODE IDE
- **컴파일러**: g++ 15.1.0 (MinGW-Builds project)
- **Python**: 3.x (FastAPI 프로젝트용)
- **버전 관리**: Git

## 🚀 빠른 시작

### Problem 1: Log File Manager
**Windows 환경:**
```cmd
cd problem1_logfilemanager
g++ -std=c++14 main.cpp LogFileManager.cpp -o test
.\test.exe
```

### Problem 2: Circular Buffer
**Windows 환경:**
```cmd
cd problem2_container
g++ -std=c++14 -Wall -Wextra -O2 -o circular_buffer_test main.cpp
.\circular_buffer_test.exe
```

### Problem 4: RESTful API


### 1. 의존성 설치

```cmd
pip install -r requirements.txt
```

### 2. 데이터베이스 초기화

#### 처음 설치 시 또는 완전 초기화 (권장)
```cmd
python fresh_start.py
```

#### 기존 방법 (관리자 계정만 생성)
```cmd
python init_db.py
```

#### 데이터베이스 완전 초기화 옵션
- **fresh_start.py**: 모든 데이터 삭제 후 테이블 재생성 + 관리자 계정 생성
- **reset_db.py**: 테이블만 삭제 후 재생성 (관리자 계정 별도 생성 필요)
- **수동 삭제**: `library.db` 파일 삭제 후 `init_db.py` 실행

### 3. 서버 실행

```cmd
python main.py
```

또는

```cmd
uvicorn main:app --reload --host 0.0.0.0 --port 8000
```

```cmd
python test.py
```

## 📁 프로젝트 구조

```
rgt_problem/
├── problem1_logfilemanager/     # C++ 로그 파일 관리자
│   ├── LogFileManager.h      # 클래스 선언
│   ├── LogFileManager.cpp    # 클래스 구현 (중복 메시지 방지 개선)
│   ├── main.cpp             # 테스트 프로그램 (로그 정리 기능 포함)
│   ├── Makefile            # 빌드 스크립트
│   ├── README.md           # 프로젝트 설명
│   ├── test.exe            # 실행 파일 (Windows)
│   ├── error.log           # 에러 로그 파일 (실행 후 생성)
│   ├── debug.log           # 디버그 로그 파일 (실행 후 생성)
│   └── info.log            # 정보 로그 파일 (실행 후 생성)
├── problem2_container/      # C++ 원형 버퍼 컨테이너
│   ├── CircularBuffer.h     # 템플릿 클래스 선언
│   ├── CircularBuffer.tpp   # 템플릿 메서드 구현
│   ├── main.cpp             # 테스트 프로그램
│   ├── Makefile             # 빌드 스크립트
│   ├── README.md            # 상세 문서
│   └── circular_buffer_test.exe  # 실행 파일
ploblem4_restapi/
│   ├── main.py              # 메인 애플리케이션
│   ├── database.py          # 데이터베이스 설정
│   ├── models.py            # 데이터베이스 모델
│   ├── schemas.py           # Pydantic 스키마
│   ├── auth.py              # 인증 관련 함수
│   ├── auth_routes.py       # 인증 API 라우터
│   ├── book_routes.py       # 도서 관리 API 라우터
│   ├── loan_routes.py       # 대출/반납 API 라우터
│   ├── init_db.py           # 데이터베이스 초기화
│   ├── fresh_start.py       # 데이터베이스 완전 초기화
│   ├── reset_db.py          # 데이터베이스 테이블 초기화
│   ├── test.py              # API 테스트 스크립트
│   ├── requirements.txt     # 의존성 패키지
│   └── README.md            # 프로젝트 설명서
└── README.md                # 전체 프로젝트 설명서
```

## 🎯 핵심 성과

- ✅ **STL 호환성**: Problem 2에서 완전한 STL 호환 컨테이너 구현
- ✅ **템플릿 메타프로그래밍**: 제네릭 프로그래밍 활용
- ✅ **RESTful API 설계**: FastAPI를 활용한 현대적 API 구현
- ✅ **예외 안전성**: RAII 원칙과 예외 처리 적용
- ✅ **문서화**: 상세한 README와 코드 주석 작성

## 📚 기술 스택

| 문제 | 언어 | 주요 라이브러리/기술 |
|------|-----|--------------------|
| Problem 1 | C++ | STL, 파일 I/O |
| Problem 2 | C++ | STL, 템플릿, Iterator |
| Problem 4 | Python | FastAPI, SQLite, JWT |

## 🔧 빌드 및 실행

각 문제별로 독립적인 빌드 시스템을 제공합니다:

- **C++ 프로젝트**: Makefile 또는 직접 g++ 컴파일
- **Python 프로젝트**: pip를 통한 의존성 설치

## 📖 상세 문서

각 문제에 대한 상세한 구현 설명, 아키텍처 설계, 사용법, 터미널 출력 값, 실행 동영상은 하단의 Notion 문서참고바랍니다.

https://www.notion.so/RGT-2996a63aee9b8076a749c32f0796ba0d


## 👨‍💻 개발자

**RGT Problem Solutions** - Robot Global Team 면접전 수행과제 

---

*알지티는 로봇을 접한 모든 사람에게 좋은 추억을 제공하는 회사입니다*
