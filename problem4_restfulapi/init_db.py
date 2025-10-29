from sqlalchemy.orm import Session
from database import SessionLocal, engine
from models import Base, User
from auth import get_password_hash
import os

def create_admin_user():
    """관리자 계정 생성"""
    # 데이터베이스 테이블 생성
    Base.metadata.create_all(bind=engine)
    
    db = SessionLocal()
    try:
        # 관리자 계정이 이미 존재하는지 확인
        admin_user = db.query(User).filter(User.username == "admin").first()
        if admin_user:
            print("Admin user already exists")
            return
        
        # 관리자 계정 생성
        admin_password = os.getenv("ADMIN_PASSWORD", "admin123")
        if len(admin_password) > 72:
            admin_password = admin_password[:72]
            
        admin_user = User(
            username=os.getenv("ADMIN_USERNAME", "admin"),
            email=os.getenv("ADMIN_EMAIL", "admin@library.com"),
            full_name="Administrator",
            hashed_password=get_password_hash(admin_password),
            is_admin=True
        )
        
        db.add(admin_user)
        db.commit()
        print("Admin user created successfully")
        
    except Exception as e:
        print(f"Error creating admin user: {e}")
        db.rollback()
    finally:
        db.close()

if __name__ == "__main__":
    create_admin_user()
