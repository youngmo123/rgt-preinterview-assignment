import os
from database import engine
from models import Base

def reset_database():
    """데이터베이스를 완전히 초기화합니다."""
    try:
        # 모든 테이블 삭제
        Base.metadata.drop_all(bind=engine)
        print("모든 테이블이 삭제되었습니다.")
        
        # 테이블 다시 생성
        Base.metadata.create_all(bind=engine)
        print("테이블이 다시 생성되었습니다.")
        
        print("데이터베이스 초기화가 완료되었습니다.")
        
    except Exception as e:
        print(f"데이터베이스 초기화 중 오류 발생: {e}")

if __name__ == "__main__":
    reset_database()
