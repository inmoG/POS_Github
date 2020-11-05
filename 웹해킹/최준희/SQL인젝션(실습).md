# SQL 인젝션 기초(실습)
MySQL + Apache + PhP = APMSetup 
- APMsetup 설치법

구글 -> APMsetup 검색(https://www.comcbt.com/xe/comtip/2642491) 후 다운로드 -> 설치 완료 후 -> 구글에 url 입력 창에 127.0.0.1 입력 -> APMsetup 설치 확인.  

## cmd 명령어
- **mysql -u root -p** : root 사용자를 이용해 패스워드 입력 명령어 (초기 패스워드 : apmsetup)
- **show databases;** : 데이터베이스 확인 명령어
- **show tables;** : 테이블 확인 명령어
- **select database();** : 현재 선택된 데이터베이스 보기 명령어
- **use [NAME];** : NAME이라는 데이터베이스 선택 명령어
- **select version();** : 버전 확인 명령어
- **select user();** : 사용자 확인 명령어
- **update mysql.user set password=password('하고싶은 패스워드') where user='root';** : mysql 패스워드 변경 명령어
- **flush privileges;** : 변경한 내용 적용 명령어
- **exit** : 서버 종료(나가기) 명령어
- **describe [NAME];** = **desc [NAME];**  : NAME이라는 테이블 구조 확인 명령어
- **select * from [NAME];** : NAME 이라는 테이블에서 모든 컬럼의 데이터 보기
- **select ascii('@@@');** : @@@의 아스키 코드 보기 명령어
- **select bin(ascii('@@@'));** : @@@의 아스키 코드 2진수로 보기 명령어

- **CREATE, DROP** 구문
    - CREATE 구문 - 데이터 베이스 생성
        - CREATE DATABASE [NAME]; : NAME 이라는 데이터베이스 생성 명령어
        - CREATE DATABASE test_db;
    - CREATE 구문 - 테이블 생성
        - CREATE TABLE [NAME] ([COLUMN_NAME][DATA_TYPE]);
        - CREATE TABLE test_tb (name char(20), age int);
        - EX) **create table member (seq int, name char(20), email char(50));** : member라는 이름의 자료형 int의 seq 컬럼과 자료형 char(20)의 name이라는 컬럼과 자료형 char(50)의 email이라는 컬럼의 테이블 생성
    - DROP 구문 - 데이터베이스/테이블 삭제
        - DROP [DATABASE/TABLE][NAME];
        - DROP TABLE test_tb;

- **INSERT, SELECT, UPDATE, DELETE** 구문
    - INSERT 구문 - 데이터 삽입
        - INSERT INTO [테이블 이름]([CULUMN1]...)VALUES([DATA1])...); *(주의: values에 문자를 넣을 경우 'a' 식으로 작성.)*
        - INSERT INTO test_tb (name, age) VALUES('데이터 입력',55);
    - **SELECT 구문 - 데이터 조회**
        - SELECT [COLUMN1]FROM[TABLE]WHERE[CONDITION];
        - **SELECT [name], [age] FROM [NAME];** : NAME이라는 테이블의 name, age라는 컬럼의 데이터 보기 명령어 
    - UPDATE 구문 - 데이터 수정
        - UPDATE[TABLE]SET[CULUMN]=[DATA1]WHERE[CONDITION];
        - **UPDATE [NAME] SET [name] = [exam] WHERE [seq]=[1];** : NAME이라는 테이블의 seq=1이라는 컬럼을 가진 name이라는 컬럼의 값을 exam으로 수정
    - DELETE 구문 - 데이터 삭제
        - DELETE FROM [TABLE] WHERE [CONDITION]; *(주의: where을 쓰지않으면 테이블 데이터 모두 삭제됨)*
        - DELETE FROM test_tb WHERE name='데이터입력';
