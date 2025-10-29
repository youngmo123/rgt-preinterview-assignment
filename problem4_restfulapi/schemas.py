from pydantic import BaseModel
from typing import Optional
from datetime import datetime

# 사용자 관련 스키마
class UserCreate(BaseModel):
    username: str
    email: str
    password: str
    full_name: str

class UserLogin(BaseModel):
    username: str
    password: str

class UserResponse(BaseModel):
    id: int
    username: str
    email: str
    full_name: str
    is_admin: bool
    created_at: datetime
    
    class Config:
        from_attributes = True

# 도서 관련 스키마
class BookCreate(BaseModel):
    title: str
    author: str
    isbn: str
    category: str
    total_copies: int = 1
    description: Optional[str] = None

class BookUpdate(BaseModel):
    title: Optional[str] = None
    author: Optional[str] = None
    category: Optional[str] = None
    total_copies: Optional[int] = None
    description: Optional[str] = None

class BookResponse(BaseModel):
    id: int
    title: str
    author: str
    isbn: str
    category: str
    total_copies: int
    available_copies: int
    description: Optional[str]
    created_at: datetime
    
    class Config:
        from_attributes = True

# 대출 관련 스키마
class LoanCreate(BaseModel):
    book_id: int

class LoanResponse(BaseModel):
    id: int
    user_id: int
    book_id: int
    loan_date: datetime
    due_date: datetime
    return_date: Optional[datetime]
    is_returned: bool
    book: BookResponse
    
    class Config:
        from_attributes = True

# 토큰 관련 스키마
class Token(BaseModel):
    access_token: str
    token_type: str

class TokenData(BaseModel):
    username: Optional[str] = None
