# SQL 인젝션 기초(실습)
MySQL + Apache + PhP = APMSetup 
- APMsetup 설치법

구글 -> APMsetup 검색(https://www.comcbt.com/xe/comtip/2642491) 후 다운로드 -> 설치 완료 후 -> 구글에 url 입력 창에 127.0.0.1 입력 -> APMsetup 설치 확인.  

## cmd 명령어
    - **mysql -u root -p** : root 사용자를 이용해 패스워드 입력 명령어 (초기 패스워드 : apmsetup)
    - **show databases;** : 데이터베이스 확인 명령어
    - **select version();** : 버전 확인 명령어
    - **select user();** : 사용자 확인 명령어
    - **update mysql.user set password=password('하고싶은 패스워드') where user='root';** : mysql 패스워드 변경 명령어
    - **flush privileges;** : 변경한 내용 적용 명령어
    - **exit** : 서버 종료(나가기) 명령어
    - **describe 테이블 이름;** : 테이블 구조 확인 명령어
    - **select * from 테이블이름;** : 테이블 데이터 보기
    - **select ascii('@@@');** : @@@의 아스키 코드 보기 명령어
    - **select bin(ascii('@@@'));** : @@@의 아스키 코드 2진수로 보기 명령어

- **CREATE, DROP** 구문
    - CREATE 구문 - 데이터 베이스 생성
        - CREATE DATABASE [DB_NAME]
        - CREATE DATABASE test_db;
    - CREATE 구문 - 테이블 생성
        - CREATE TABLE [NAME] ([COLUMN_NAME][DATA_TYPE]);
        - CREATE TABLE test_tb (name char(20), age int);
    - DROP 구문 - 데이터베이스/테이블 삭제
        - DROP [DATABASE/TABLE][NAME];
        - DROP TABLE test_tb;

- **INSERT, SELECT, UPDATE, DELETE** 구문
    - INSERT 구문 - 데이터 삽입
        - INSERT INTO [TABLE_NAME]([CULUMN1]...)VALUES([DATA1])...);
        - INSERT INTO test_tb (name, age) VALUES('데이터 입력',55);
    - SELECT 구문 - 데이터 조회
        - SELECT [COLUMN1]FROM[TABLE]WHERE[CONDITION];
        - SELECT name, age FROM test_tb;
    - UPDATE 구문 - 데이터 수정
        - UPDATE[TABLE]SET[CULUMN]=[DATA1]WHERE[CONDITION];
        - UPDATE test_tb SET=35 WHERE name='데이터입력';
    - DELETE 구문 - 데이터 삭제
        - DELETE FROM [TABLE] WHERE [CONDITION];
        - DELETE FROM test_tb WHERE name='데이터입력';
