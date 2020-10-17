
# 데이터베이스 
`데이터`를 구조적으로 모아둔 데이터 집합소<br></br>
![](https://postfiles.pstatic.net/MjAyMDEwMTdfNjMg/MDAxNjAyOTE5ODAwNDgx.GenBJPYFF4PaVrArg-npB31-Rj1bqYRA-Pv7PKYf4ZYg.ZDjrY71C69ntSZxoXSUJ0KHCsd5fGg062UWbtD2Sc3Ig.PNG.depeix/image.png?type=w966)<br></br>
 # 용어
(A)데이터의 집합 : 테이블, 릴레이션
(B)행 : 로우, 레코드, 튜플
(C)열 : 컬럼, 속성
<br></br>
DBMS : 데이터베이스 관리 시스템
<br></br>
RDBMS : 관계형 데이터베이스 관리 시스템, 주요기능은 데이터 추가, 수정, 삭제, 조회, 데이터 무결성 유지, 트랜젝션 관리, 백업 및 복원, 보안 등이 있다. ex) Oracle, mssql, mysql
<br></br>
SQL(Structured Query Language) : 구조화된 질의 언어

# 기본 SQL 문법 종류

# 데이터 정의어(DDL, Data Definition Language)
- 데이터베이스의 구조를 정의하거나 변경, 삭제하기 위해 사용하는 언어
- 주로 DB관리자 또는 설계자가 사용
- CREATE(개체 생성), ALTER(개체 수정), DROP(개체 삭제), TRUNCATE(개체 초기화)<br></br>

# 데이터 조작어(DML, Data Manipulation Language)
- data를 조작하기 위해 사용하는 언어
- data의 삽입, 수정, 삭제, 조회 등의 동작을 제어
- data를 이용하려는 사용자와 시스템간의 인터페이스를 직접적으로 제공하는 언어
- 가장 많이 사용됨(공격 시에도 가장 많이 사용)
- INSERT(데이터 생성), UPDATE(데이터 수정), DELETE(데이터 삭제), SELECT(데이터 조회)<br></br>

# 데이터 제어어(DCL, Data Control Language)
- DB에 대한 보안, 무결성, 복구등 DBMS를 제어하기 위한 언어
- GRANT(권한할당), REVOKE(권한해제), COMMIT(실행), ROLLBACK(복구)<br></br>

CRUD : 컴퓨터 소프트웨어가 가지는 기본적인 처리기능 Create(생성), Read(읽기), Update(갱신), Delete(삭제)

# 서브쿼리(Sub Query)
- 하나의 SQL문안에 포함되어 있는 또 다른 SQL문
- 알려지지 않은 조건에 근거한 값 들을 검색하는 SELECT 문장을 작성하는데 유용
- 메인 쿼리가 서브 쿼리를 포함하는 종속적인 관계
- SELECT, UPDATE, DELETE, INSERT와 같은 DML문과 CREATE TABLE 또는 VIEW에서 사용 가능<br></br>

# 뷰(VIEW)
- 하나 이상의 테이블(또는 다른 뷰)에서 원하는 데이터를 선택하여 새로운 가상 테이블로 만들어 주는 것
- 다른 테이블에 있는 데이터를 보여줄 뿐이며 데이터 자체를 포함하고 있는 것은 아님
- 저장장치 내에 물리적으로 존재하지 않고 가상테이블로 만들어 짐
- 논리적인 독립성을 제공<br></br>

# 뷰(View)의 장점
- 데이터베이스의 구조를 변경하여도 테이블에 의존하는 어플리케이션을 변경할 필요가 없음
- 복잡한 쿼리를 단순하게 만들 수 있어 편리함
- 사용자에게 필요 없는 정보를 숨길 수 있음<br></br>
