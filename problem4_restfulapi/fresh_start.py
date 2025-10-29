import os
from database import engine, SessionLocal
from models import Base, User
from auth import get_password_hash

def fresh_start():
    """데이터베이스를 완전히 초기화하고 관리자 계정을 생성합니다."""
    try:
        # 1. 모든 테이블 삭제
        Base.metadata.drop_all(bind=engine)
        print("✅ 모든 테이블이 삭제되었습니다.")
        
        # 2. 테이블 다시 생성
        Base.metadata.create_all(bind=engine)
        print("✅ 테이블이 다시 생성되었습니다.")
        
        # 3. 관리자 계정 생성
        db = SessionLocal()
        try:
            admin_user = User(
                username=os.getenv("ADMIN_USERNAME", "admin"),
                email=os.getenv("ADMIN_EMAIL", "admin@library.com"),
                full_name="Administrator",
                hashed_password=get_password_hash(os.getenv("ADMIN_PASSWORD", "admin123")),
                is_admin=True
            )
            
            db.add(admin_user)
            db.commit()
            print("✅ 관리자 계정이 생성되었습니다.")
            print(f"   - 사용자명: {admin_user.username}")
            print(f"   - 이메일: {admin_user.email}")
            
        except Exception as e:
            print(f"❌ 관리자 계정 생성 중 오류: {e}")
            db.rollback()
        finally:
            db.close()
        
        print("\n🎉 데이터베이스가 완전히 초기화되었습니다!")
        print("이제 test.py를 실행하여 API를 테스트할 수 있습니다.")
        
    except Exception as e:
        print(f"❌ 데이터베이스 초기화 중 오류 발생: {e}")

if __name__ == "__main__":
    fresh_start()
