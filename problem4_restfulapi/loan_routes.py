from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.orm import Session
from datetime import datetime, timedelta
from typing import List
from database import get_db
from models import Loan, Book, User
from schemas import LoanCreate, LoanResponse
from auth import get_current_user

router = APIRouter(prefix="/loans", tags=["loans"])

@router.post("/", response_model=LoanResponse)
def create_loan(
    loan: LoanCreate,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user)
):
    """도서 대출"""
    # 도서 존재 확인
    book = db.query(Book).filter(Book.id == loan.book_id).first()
    if not book:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Book not found"
        )
    
    # 대출 가능 여부 확인
    if book.available_copies <= 0:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="No available copies of this book"
        )
    
    # 사용자가 이미 같은 도서를 대출 중인지 확인
    existing_loan = db.query(Loan).filter(
        Loan.user_id == current_user.id,
        Loan.book_id == loan.book_id,
        Loan.is_returned == False
    ).first()
    
    if existing_loan:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="You already have this book on loan"
        )
    
    # 대출 기록 생성
    due_date = datetime.utcnow() + timedelta(days=14)  # 14일 대출 기간
    db_loan = Loan(
        user_id=current_user.id,
        book_id=loan.book_id,
        due_date=due_date
    )
    
    # 도서의 대출 가능 수량 감소
    book.available_copies -= 1
    
    db.add(db_loan)
    db.commit()
    db.refresh(db_loan)
    
    return db_loan

@router.get("/", response_model=List[LoanResponse])
def get_loans(
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user)
):
    """현재 사용자의 대출 목록 조회"""
    loans = db.query(Loan).filter(Loan.user_id == current_user.id).all()
    return loans

@router.put("/{loan_id}/return")
def return_book(
    loan_id: int,
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user)
):
    """도서 반납"""
    loan = db.query(Loan).filter(
        Loan.id == loan_id,
        Loan.user_id == current_user.id
    ).first()
    
    if not loan:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Loan not found"
        )
    
    if loan.is_returned:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Book already returned"
        )
    
    # 반납 처리
    loan.is_returned = True
    loan.return_date = datetime.utcnow()
    
    # 도서의 대출 가능 수량 증가
    book = db.query(Book).filter(Book.id == loan.book_id).first()
    book.available_copies += 1
    
    db.commit()
    
    return {"message": "Book returned successfully"}

@router.get("/me/loans", response_model=List[LoanResponse])
def get_my_loans(
    db: Session = Depends(get_db),
    current_user: User = Depends(get_current_user)
):
    """내 대출 목록 조회 (이미지 예시의 엔드포인트)"""
    loans = db.query(Loan).filter(
        Loan.user_id == current_user.id,
        Loan.is_returned == False
    ).all()
    return loans
