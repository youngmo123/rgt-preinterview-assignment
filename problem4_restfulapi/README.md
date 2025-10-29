# Library Management System API

온라인 도서관 관리 시스템을 위한 RESTful API 서버입니다. FastAPI 프레임워크를 사용하여 구현되었습니다.

## 주요 기능

- **사용자 인증**: 회원가입, 로그인, JWT 토큰 기반 인증
- **도서 관리**: 도서 등록, 조회, 검색, 삭제 (관리자 기능)
- **대출/반납**: 도서 대출, 반납, 대출 이력 조회
- **권한 관리**: 일반 사용자와 관리자 권한 구분

## 기술 스택

- **FastAPI**: 현대적인 Python 웹 프레임워크
- **SQLAlchemy**: ORM (Object-Relational Mapping)
- **SQLite**: 데이터베이스 (개발용)
- **JWT**: JSON Web Token 인증
- **Pydantic**: 데이터 검증 및 직렬화
- **Uvicorn**: ASGI 서버

## 프로젝트 구조

```
ploblem4_restapi/
├── main.py              # 메인 애플리케이션
├── database.py          # 데이터베이스 설정
├── models.py            # 데이터베이스 모델
├── schemas.py           # Pydantic 스키마
├── auth.py              # 인증 관련 함수
├── auth_routes.py       # 인증 API 라우터
├── book_routes.py       # 도서 관리 API 라우터
├── loan_routes.py       # 대출/반납 API 라우터
├── init_db.py           # 데이터베이스 초기화
├── fresh_start.py       # 데이터베이스 완전 초기화
├── reset_db.py          # 데이터베이스 테이블 초기화
├── test.py              # API 테스트 스크립트
├── requirements.txt     # 의존성 패키지
└── README.md           # 프로젝트 설명서
```

## 설치 및 실행

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

### 4. API 문서 확인

서버 실행 후 브라우저에서 다음 URL로 접속:
- **Swagger UI**: http://localhost:8000/docs
- **ReDoc**: http://localhost:8000/redoc

## API 엔드포인트

### 인증 (Authentication)
- `POST /auth/signup` - 회원가입
- `POST /auth/login` - 로그인

### 도서 관리 (Books)
- `POST /books` - 도서 등록 (관리자만)
- `GET /books` - 도서 목록 조회/검색
- `GET /books/{book_id}` - 특정 도서 조회
- `DELETE /books/{book_id}` - 도서 삭제 (관리자만)

### 대출/반납 (Loans)
- `POST /loans` - 도서 대출
- `GET /loans` - 내 대출 목록
- `GET /users/me/loans` - 현재 대출 중인 도서 목록
- `PUT /loans/{loan_id}/return` - 도서 반납

## 기본 계정

- **관리자 계정**:
  - Username: `admin`
  - Password: `admin123`
  - Email: `admin@library.com`

## API 테스트

### 완전 초기화 후 테스트 (권장)

1. **데이터베이스 완전 초기화**
   ```cmd
   python fresh_start.py
   ```

2. **서버 실행**
   ```cmd
   python main.py
   ```

3. **API 테스트 (새 터미널에서)**
   ```cmd
   python test.py
   ```

### 테스트 스크립트 내용

이 스크립트는 다음 작업들을 순차적으로 수행합니다:
1. 사용자 회원가입
2. 사용자 로그인
3. 관리자 로그인
4. 도서 등록
5. 도서 검색
6. 도서 대출
7. 대출 목록 조회

## 데이터베이스 모델

### User (사용자)
- `id`: 사용자 ID (Primary Key)
- `username`: 사용자명 (Unique)
- `email`: 이메일 (Unique)
- `full_name`: 전체 이름
- `hashed_password`: 해시된 비밀번호
- `is_admin`: 관리자 여부
- `created_at`: 생성일시

### Book (도서)
- `id`: 도서 ID (Primary Key)
- `title`: 제목
- `author`: 저자
- `isbn`: ISBN (Unique)
- `category`: 카테고리
- `total_copies`: 총 권수
- `available_copies`: 대출 가능 권수
- `description`: 설명
- `created_at`: 등록일시

### Loan (대출)
- `id`: 대출 ID (Primary Key)
- `user_id`: 사용자 ID (Foreign Key)
- `book_id`: 도서 ID (Foreign Key)
- `loan_date`: 대출일
- `due_date`: 반납 예정일
- `return_date`: 실제 반납일
- `is_returned`: 반납 여부

## 보안 기능

- **JWT 토큰 인증**: Bearer 토큰 기반 인증
- **비밀번호 해싱**: bcrypt를 사용한 안전한 비밀번호 저장
- **권한 기반 접근 제어**: 관리자와 일반 사용자 권한 구분
- **데이터 검증**: Pydantic을 통한 입력 데이터 유효성 검사

## 환경 변수

프로젝트 루트에 `.env` 파일을 생성하여 다음 환경 변수를 설정할 수 있습니다:

```env
DATABASE_URL=sqlite:///./library.db
SECRET_KEY=your-secret-key-here-change-in-production
ALGORITHM=HS256
ACCESS_TOKEN_EXPIRE_MINUTES=30
ADMIN_USERNAME=admin
ADMIN_EMAIL=admin@library.com
ADMIN_PASSWORD=admin123
```

## 개발자 정보

이 프로젝트는 Robot Global Team의 Python 코딩 과제로 개발되었습니다.
