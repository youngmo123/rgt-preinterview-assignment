import requests

base_url = "http://localhost:8000"

# 1. 사용자 회원가입
signup_data = {
    "username": "john_doe",
    "email": "john@example.com", 
    "password": "securepass123",
    "full_name": "John Doe"
}
response = requests.post(f"{base_url}/auth/signup", json=signup_data)
print(f"회원가입 응답: {response.status_code}")
if response.status_code == 200:
    print(f"회원가입 결과: {response.json()}")
else:
    print(f"회원가입 오류: {response.json()}")

# 2. 사용자 로그인
login_data = {"username": "john_doe", "password": "securepass123"}
auth_response = requests.post(f"{base_url}/auth/login", json=login_data)
token = auth_response.json()["access_token"]
headers = {"Authorization": f"Bearer {token}"}
print(f"로그인 응답: {auth_response.status_code}")
print(f"토큰 획득 성공")

# 3. 관리자 로그인 (도서 등록용)
admin_login_data = {"username": "admin", "password": "admin123"}
admin_auth_response = requests.post(f"{base_url}/auth/login", json=admin_login_data)
admin_token = admin_auth_response.json()["access_token"]
admin_headers = {"Authorization": f"Bearer {admin_token}"}
print(f"관리자 로그인 응답: {admin_auth_response.status_code}")

# 4. 도서 등록
book_data = {
    "title": "Python Programming",
    "author": "John Smith",
    "isbn": "978-0123456789",
    "category": "Programming",
    "total_copies": 5
}
book_response = requests.post(f"{base_url}/books", json=book_data, headers=admin_headers)
print(f"도서 등록 응답: {book_response.status_code}")
if book_response.status_code == 200:
    book_info = book_response.json()
    print(f"등록된 도서: {book_info['title']} by {book_info['author']}")
else:
    print(f"도서 등록 오류: {book_response.json()}")

# 5. 도서 검색
search_response = requests.get(f"{base_url}/books?category=Programming&available=true")
print(f"도서 검색 응답: {search_response.status_code}")
books = search_response.json()
print(f"검색된 도서 수: {len(books)}")
for book in books:
    print(f"- {book['title']} by {book['author']} (대출가능: {book['available_copies']}권)")

# 6. 도서 대출 (user_id는 API에서 자동으로 처리)
borrow_data = {"book_id": 1}  # user_id 제거 - API에서 현재 사용자 ID 자동 사용
borrow_response = requests.post(f"{base_url}/loans", json=borrow_data, headers=headers)
print(f"도서 대출 응답: {borrow_response.status_code}")
if borrow_response.status_code == 200:
    loan_info = borrow_response.json()
    print(f"대출 성공! 대출 ID: {loan_info['id']}, 반납일: {loan_info['due_date']}")

# 7. 내 대출 목록 조회 (수정된 엔드포인트)
loans_response = requests.get(f"{base_url}/loans/me/loans", headers=headers)
print(f"대출 목록 응답: {loans_response.status_code}")
if loans_response.status_code == 200:
    loans = loans_response.json()
    print(f"현재 대출 중인 도서 수: {len(loans)}")
    for loan in loans:
        print(f"- {loan['book']['title']} by {loan['book']['author']} (반납일: {loan['due_date']})")

print("\n=== 모든 테스트 완료 ===")
