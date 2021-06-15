# SQL 인젝션 기초(이론)
- 데이터베이스 (Database : DB)
    - 데이터를 구조적으로 모아둔 데이터 집합소 = 즉, 데이터를 저장하는 저장소

- 관계형 데이터 베이스 (Relational Database : RDB)
    - 데이터를 **열**과 **행**을 가진 테이블 형태로 표현하며, 구조적으로 데이터 관리를 한다.

- 관계형 데이터 베이스 관리 시스템 (Relational Database Managerment System : RDBMS)
    - 관계형 데이터베이스를 관리하는 시스템을 RDBMS라고 한다. 주요 기능은 **데이터 추가**, **수정**, **삭제**, **조회**, **데이터 무결성 유지** *(컴퓨팅 분야에서 완전한 수명 주기를 거치며 데이터의 정확성과 일관성을 유지하고 보증하는 것)*, **트랜젝션 관리** *(온라인 응용 프로그램의 처리를 어떤 방법으로 분할하여 관리하는 수법.)*, **백업 및 복원**, **보안** 등이 있다.

## SQL (Structured Query Language)
- RDBMS의 데이터를 관리하기 위해 설계된 특수 목적의 프로그래밍 언어'

**문법 종류**
1. 데이터 정의 언어 (Data Definition Language : DDL)
2. **데이터 조작 언어** (Data Manupulation Language : DML)
- **CRUD** (create : 생성, read : 읽기, update : 갱신, delete : 삭제)
    - 대부분 컴퓨터 소프트웨어가 가지는 기본적인 데이터 처리 기능.
3. 데이터 제어 언어 (Data Control Language : DCL)

## 연산자
1. 연산자와 피연산자의 관계

    ex) 5(피연산자) **+(연산자)** 3(피연산자)

2. 산술 연산자 (+, -, *, /)
3. 비교 연산자 (<, >, <=, >=, !=, =, <>)
4. 논리 연산자 (우선 순위별로 NOT >> AND >> OR)
5. 비트 논리 연산자 (오라클 -> &, mssql -> |, mysql -> ^)
6. 연결 연산자 (오라클 -> ||, mssql -> +, mysql -> 공백)
7. IN 연산자 ([컬럼/값] IN (값1, 값2...))
8. NOT IN 연산자 ([컬럼/값] NOT IN (값1, 값2...))
9. LIKE 연산자
    - % -> 모든 문자 -> ex) id like '%ad%'
    - _ -> 하나의 문자 -> ex) id like 'ad_'

## 함수
`오라클 --> SUBSTR, SUBSTRB`<BR/>
`MSSQL --> SUBSTRING`<BR/>
`MYSQL --> SUBSTRING, SUBSTR, MID`<BR/>

- 문자, 아스키 코드 변환 함수
    - 오라클<BR/>
        (CHAR -> ASCII) => ASCII<BR/>
        (ASCII -> CHAR) => CHR
    - MSSQL<BR/>
        (CHAR -> ASCII) => ASCII<BR/>
        (ASCII -> CHAR) => CHAR
    - MYSQL<BR/>
        (CHAR -> ASCII) => ASCII, ORD<BR/>
        (ASCII -> CHAR) => CHAR

- COUNT 함수
    - SELECT COUNT(CULUMN) FROM [TABLE]

- 길이 함수
    - 오라클 --> LENGTH
    - MSSQL --> LEN
    - MYSQL --> LENGTH

## 조건문
- ORACLE --> DECODE 함수 CASE WHEN 구문
- MSSQL --> CASE WHEN 구문
- MYSQL --> IF 함수, CASE WHEN 구문<BR/>
**CASE WHEN [CONDITHON] THEN [TRUE] ELSE [FALSE] END** : CONDITION의 조건이 참일 경우 TRUE가 실행되고 거짓일 경우 FALSE가 실행됨.

## 서브 쿼리(SubQuery)
- **select** 절에 있는 서브쿼리 : 스칼라 서브쿼리 : 하나의 레코드에 하나의 컬럼만 반환할 수 있는 서브쿼리 *(다수의 행에 다수의 컬럼이 반환이 되면 에러가 발생)* 
- **from** 절에 있는 서브쿼리 : 인라인 뷰 : 가상의 테이블 (제약 조건이 없음)
- **where** 절에 있는 서브쿼리 : 일반 서브쿼리(서브쿼리)<BR/>

**서브쿼리의 종류**
- 단일 행 서브쿼리 : 하나의 레코드만 반환해야 하는 서브쿼리<BR/>
SELECT [name],[email] FROM [NAME] WHERE id=(SELECT id FROM bbs where idx=192);<BR/>
- 다중 행 서브쿼리 : 두개 이상의 레코드까지 반환할 수 있는 서브쿼리<BR/>
SELECT [name],[email] FROM [NAME] WHERE id in (SELECT id FROM bbs);





        