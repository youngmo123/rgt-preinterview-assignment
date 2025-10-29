from fastapi import APIRouter, Depends, HTTPException, status, Query
from sqlalchemy.orm import Session
from typing import List, Optional
from database import get_db
from models import Book, User
from schemas import BookCreate, BookUpdate, BookResponse
from auth import get_current_user, get_current_admin_user

router = APIRouter(prefix="/books", tags=["books"])

@router.post("/", response_model=BookResponse)
def create_book(
    book: BookCreate,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_admin_user)
):
    """도서 등록 (관리자만 가능)"""
    # ISBN 중복 확인
    existing_book = db.query(Book).filter(Book.isbn == book.isbn).first()
    if existing_book:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Book with this ISBN already exists"
        )
    
    db_book = Book(
        title=book.title,
        author=book.author,
        isbn=book.isbn,
        category=book.category,
        total_copies=book.total_copies,
        available_copies=book.total_copies,
        description=book.description
    )
    db.add(db_book)
    db.commit()
    db.refresh(db_book)
    
    return db_book

@router.get("/", response_model=List[BookResponse])
def get_books(
    category: Optional[str] = Query(None, description="카테고리로 필터링"),
    available: Optional[bool] = Query(None, description="대출 가능 여부로 필터링"),
    search: Optional[str] = Query(None, description="제목이나 저자로 검색"),
    db: Session = Depends(get_db)
):
    """도서 목록 조회 및 검색"""
    query = db.query(Book)
    
    # 카테고리 필터링
    if category:
        query = query.filter(Book.category == category)
    
    # 대출 가능 여부 필터링
    if available is not None:
        if available:
            query = query.filter(Book.available_copies > 0)
        else:
            query = query.filter(Book.available_copies == 0)
    
    # 제목이나 저자로 검색
    if search:
        query = query.filter(
            (Book.title.contains(search)) | (Book.author.contains(search))
        )
    
    books = query.all()
    return books

@router.get("/{book_id}", response_model=BookResponse)
def get_book(book_id: int, db: Session = Depends(get_db)):
    """특정 도서 조회"""
    book = db.query(Book).filter(Book.id == book_id).first()
    if not book:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Book not found"
        )
    return book

@router.delete("/{book_id}")
def delete_book(
    book_id: int,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_admin_user)
):
    """도서 삭제 (관리자만 가능)"""
    book = db.query(Book).filter(Book.id == book_id).first()
    if not book:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Book not found"
        )
    
    # 대출 중인 도서가 있는지 확인
    if book.available_copies < book.total_copies:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Cannot delete book with active loans"
        )
    
    db.delete(book)
    db.commit()
    
    return {"message": "Book deleted successfully"}
