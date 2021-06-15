# SQL Injection
</br></br>

# 개념

`SQL Injection`은 클라이언트에서 웹 응용프로그램으로 `SQL 쿼리`를 삽입하여 웹 서버와 연결된 `데이터베이스`에 비정상적인 접근 및 명령어를 실행할 수 있는 공격이다.</br>
이를 통해 인증우회, 권한상승, 데이터베이스 내 데이터 열람 및 조작 등의 공격이 가능하다.
</br></br>

# SQL 동작 방식

![](https://images.velog.io/images/kmk9502/post/78c7824c-fd59-4b68-89df-6e744313f8d6/SQL%20Injection%20Low%20%EB%A0%88%EB%B2%A8%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

1. 사용자가 입력한 값이 `$id` 변수로 입력된다.
2. 입력된 $id 변수는 사용자의 이름과 성을 조회하는 SQL문에서 `사용자를 구분`하는 변수로 사용된다(user_id의 값). </br>이러한 SQL 문은 ` $query` 변수에 저장된다.
3. ` $query` 변수는 `MySQLi_query()` 함수를 통해 데이터베이스에 쿼리 문자열로 전송되며 결과는 ` $result`에 저장된다.
4. MySQLi_query()를 통해 얻은 ` $result` 변수는 ` $query`의 실행결과를 가지고 있으며, `while 문`과 `MySQLi_fetch_assoc()` 함수를 통해 레코드를 1개씩 반환받은 후 데이터베이스 내의 first_name과 last_name을 각각` $first`와` $last` 변수에 저장한다.
5. 마지막으로 `echo문`을 통해 $id, $first, $last 값을 웹 페이지에 `출력`한다.</br></br>

-   ## SQL 동작 원리</br></br>
    -   웹 브라우저 <-> 웹 서버 <-> php파서 or asp or jsp 등 서버 사이드 언어 <-> 데이터베이스</br></br>
    -   공격자는 위의 과정에서 존재하는 `취약점`을 악용하여 SQL Injection 공격을 진행한다.
</br></br></br></br></br>

# 공격
</br></br>

# Low 레벨

![](https://images.velog.io/images/kmk9502/post/78c7824c-fd59-4b68-89df-6e744313f8d6/SQL%20Injection%20Low%20%EB%A0%88%EB%B2%A8%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

$query 변수의 내용 중 ` $id` 부분을 보면 가변적인 데이터 입력 값($id)에 대한 필터링이 존재하지 않는다.</br>이는 `추가적인 쿼리 요청`이 가능하다는 의미이며, 이를 통해 데이터베이스 관련 추가 정보들을 `획득`하거나 `변조`하여 공격에 </br>활용할 수 있다.
</br></br>

## 1) 특정 사용자 이름 확인

![](https://images.velog.io/images/kmk9502/post/6a81e57f-27a3-4f18-831a-8f53715d002e/SQL%20%EC%B7%A8%EC%95%BD%EC%A0%90%20%ED%99%95%EC%9D%B8.png)

User ID 부분에 숫자 1을 입력 후 제출하면 ID가 1인 사용자의 정보가 화면에 출력된다. </br>
즉, 데이터베이스는 `User ID`에 해당하는 정보를 찾아온다고 추정할 수 있다.</br>
</br>

## 2) 전체 사용자 정보 확인

![](https://images.velog.io/images/kmk9502/post/c288f3ce-0f2a-4260-bddd-35d16935ed69/or%20%EA%B5%AC%EB%AC%B8%EC%9D%84%20%EC%9D%B4%EC%9A%A9%ED%95%9C%20%EC%82%AC%EC%9A%A9%EC%9E%90%20%EA%B3%84%EC%A0%95%20%EC%A0%95%EB%B3%B4%20%EC%A1%B0%ED%9A%8C.png)

입력 값으로 `99' or '1'='1`이라는 값을 입력후 전송한 결과이다. 전송한 명령 코드는 </br>
`SELECT first_name, last_name FROM users WHERE user_id = '99' or '1'='1'`과 같은 쿼리문이 된다. </br> 이 쿼리문은 `or` 연산자로 인해 id가 99인 사용자가 없더라도 `1=1`이 항상 참이 된다. </br>
따라서 쿼리는 항상 참인 조건을 호출하였으므로 모든 사용자의 정보를 얻을 수 있게 된다.
</br></br>

![](https://images.velog.io/images/kmk9502/post/3bb686c6-7867-453e-8d8e-3c42c9adb777/%EC%9A%B0%EB%AC%BC%20%EC%A0%95%20%EC%9E%90%20%EB%AC%B8%EC%9E%90%EB%A5%BC%20%EC%9D%B4%EC%9A%A9%ED%95%9C%20where%20%EA%B5%AC%EB%AC%B8%20%EC%9A%B0%ED%9A%8C.png)

또한, 주석을 의미하는 `#` 문자를 이용하여 `where` 조건문의 실행을 막을 수 있다. </br>
`#` 뒤에 오는 SQL 쿼리는 주석처리 되어 where 조건문이 실행되지 않으므로 SQL 쿼리는 </br>
`SELECT first_name, last_name FROM users`가 된다.
</br></br>

## 3) 데이터베이스 버전 및 호스트 명 확인

`UNION` 구문을 사용하여 데이터베이스의 버전, 컬럼 명 등을 확인할 수 있다. 

  - ### UNION 구문
    - SQL 쿼리문이 조회하는 `select`문의 컬럼 갯수와 union 뒤의 `select` 구문의 컬럼 갯수가 같아야 union을 사용할 수 있다. </br> 따라서 SQL 쿼리문이 몇 개의 컬럼을 가지고 있는지 확인해야 한다.
</br></br></br>

union 구문을 활용해 대상 서버가 어떤 데이터베이스를 사용 중인지 확인해 보자. 

![](https://images.velog.io/images/kmk9502/post/5fb0082e-0de7-4987-be37-5c03e0181d10/%EB%B2%84%EC%A0%84%20%ED%99%95%EC%9D%B8%20%EC%8B%9C%20%EC%98%A4%EB%A5%98%20%EB%A9%94%EC%8B%9C%EC%A7%80.png)

위 사진에서 보이는 오류 메시지는 `'union select @@version#`을 요청한 결과이다. </br>
요청한 SQL 쿼리와 데이터베이스 컬럼의 개수가 맞지 않는다. </br>
따라서 현재 select 뒤의 컬럼 개수는 1개이지만, 실제로는 그 이상의 컬럼이 존재한다는 것을 알 수 있다.</br></br>

![](https://images.velog.io/images/kmk9502/post/721d30fc-e98a-4ff6-a8b8-eaaf0e7e641a/union%20%EA%B5%AC%EB%AC%B8%20%EC%9D%B4%EC%9A%A9%EC%9D%84%20%EC%9C%84%ED%95%B4%20%EC%BB%AC%EB%9F%BC%20%EA%B0%9C%EC%88%98%20%EB%A7%9E%EC%B6%94%EA%B8%B0.png)

`UNION 연산자`를 이용하여 select 뒤에 아무 문자나 넣어서 컬럼 개수를 맞춰주고, 버전 확인 명령어를 입력하면 데이터베이스 버전이 출력된다.</br>
입력값: `'union select 1, @@version#`</br></br>

 `@@` 뒤에 여러 문자를 넣을 수 있는데, `@@hostname#`의 경우 서버의 호스트 이름을 확인할 수 있다.
 </br></br>


## 4) 필드 개수 확인

필드 개수는 SQL 쿼리에서 `order by` 로 확인할 수 있다. 'order by'는 `컬럼을 기준으로 정렬`을 의미한다.</br>예를 들어 `order by 3#`의 의미는 3번째 컬럼을 기준으로 정렬하라는 쿼리문이다.

![](https://images.velog.io/images/kmk9502/post/bb2f75c6-cc1c-4925-8879-ec60d592c888/order%20by%20%EC%8B%A4%ED%96%89%20%EC%8B%9C%20%EC%98%A4%EB%A5%98.png)

오류가 발생했다. 오류 내용을 확인해보니 3번째 컬럼이 존재하지 않는 것을 확인할 수 있다.</br>
따라서 3개 이하로 컬럼 개수를 수정해보자.</br></br>

![](https://images.velog.io/images/kmk9502/post/7381473d-e17e-4585-b632-77288f23d37a/order%20by%20%EC%8B%A4%ED%96%89%20%EC%84%B1%EA%B3%B5.png)

컬럼 개수를 2개로 설정한 결과이다. 정상적으로 응답하는 것을 확인할 수 있다.
</br></br>

## 5) 시스템 사용자 확인

`system_user(), user()` 함수를 이용하여 공격 대상의 현재 구동 중인 `데이터베이스`와 데이터베이스가 가지고 있는 `권한`을 확인할 수 있다. </br> 
이를 통해 공격 대상 데이터베이스가 어떠한 권한으로 쿼리를 넘기는지 알 수 있다.

![](https://images.velog.io/images/kmk9502/post/9867f1c0-9177-46cc-858e-046d27d37abb/%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%B2%A0%EC%9D%B4%EC%8A%A4%20%ED%98%B8%EC%8A%A4%ED%8A%B8%EB%AA%85%EA%B3%BC%20%ED%98%84%EC%9E%AC%20%EC%82%AC%EC%9A%A9%EC%9E%90%20%ED%99%95%EC%9D%B8.png)

위 사진에서 데이터베이스 호스트명과 현재 사용자를 확인할 수 있다.
</br> </br> 

## 6) 현재 데이터베이스명 확인

`database()` 함수를 이용하여 현재 웹 페이지와 연결된 데이터베이스 확인이 가능하다. 

![](https://images.velog.io/images/kmk9502/post/435b341c-4389-4469-b861-9cc9506b0547/%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%B2%A0%EC%9D%B4%EC%8A%A4%EB%AA%85%20%ED%99%95%EC%9D%B8.png)

해당 웹페이지와 연결된 데이터베이스는 dvwa라는 것을 확인할 수 있다.
</br> </br> 

## 7) MySQL 내 존재하는 데이터베이스 확인

`information_schema`를 통해 MySQL 내 존재하는 데이터베이스를 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/3b158d53-e4f5-4d03-82ae-e0dbc322c4ac/information_schema%EC%97%90%EC%84%9C%20%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%B2%A0%EC%9D%B4%EC%8A%A4%20%ED%99%95%EC%9D%B8.png)

- ### information_schema
  - 데이터에 의한 데이터, 즉 메타 데이터(Metadata)로써 `데이터 사전`을 의미한다. </br>  데이터 사전이란 데이터베이스에 속한 데이터들의 정보를 저장한 `중앙 저장소`를 의미한다. </br>  information_schema는 `읽기 전용`으로 사용자가 직접 수정하거나 관여할 수 없다.
- ### schemata 테이블
  - information_schema 내에 존재하는 테이블 중 `schemata` 테이블은 데이터베이스의 정보를 제공한다.
- ### schema_name
  - 데이터베이스의 이름을 의미한다.
</br> </br> 

## 8) DVWA 내에 있는 테이블 확인

데이터베이스 목록을 확인 했으니 공격 대상의 데이터베이스에 대한 세부정보를 확인한다. </br>  `table_name`에서 `user_id, password 컬럼`을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/fabe097e-7556-4cf3-a16a-b4336e3a57d3/DVWA%20%EB%82%B4%20%ED%85%8C%EC%9D%B4%EB%B8%94%20%EB%AA%A9%EB%A1%9D%20%ED%99%95%EC%9D%B8.png)

위 사진의 ID란에 적혀있는 union 구문을 보면 `dvwa 테이블 내`의 `information_schema.tables 내`에 존재하는 </br>  `table_name`에서 user_id 컬럼과 password 컬럼을 확인할 수 있다.
</br>  </br>  

## 9) 테이블 구조(열) 확인

테이블을 확인했으니 이제 `users 테이블`의 `컬럼 이름`을 확인해 보자. 

![](https://images.velog.io/images/kmk9502/post/f70d003b-70b7-4ab4-acef-300c1f00f068/%ED%85%8C%EC%9D%B4%EB%B8%94%20%EA%B5%AC%EC%A1%B0(%EC%97%B4)%20%ED%99%95%EC%9D%B8.png)

위 사진은 `users 테이블` 내의 `information_schema.columns` 내의 컬럼 이름들이다.
</br>  </br>  

## 10) 사용자명과 패스워드 확인

이전 공격에서 users 테이블에 password 컬럼이 존재한다는 것을 확인했다. 이제 password 컬럼을 조회해 보자.

![](https://images.velog.io/images/kmk9502/post/466df658-a0d9-42e9-9466-6f54e5825200/users%20%ED%85%8C%EC%9D%B4%EB%B8%94%EC%9D%98%20%EC%82%AC%EC%9A%A9%EC%9E%90%20%ED%8C%A8%EC%8A%A4%EC%9B%8C%EB%93%9C%20%ED%99%95%EC%9D%B8.png)

password 컬럼을 조회하여 해쉬 값으로 이루어진 것으로 보이는 각 사용자의 패스워드를 확인할 수 있다.</br> `MD5` 형태로 이루어진 해쉬 값을 복원해 보도록 하자.

![](https://images.velog.io/images/kmk9502/post/34fe5c91-091f-41cf-90c5-ef1f2f502542/%ED%95%B4%EC%89%AC%20%EA%B0%92%20%EB%94%94%EC%BD%94%EB%93%9C.png)

MD5 디코드 결과 admin 계정의 비밀번호는 password인 것을 확인할 수 있다.
</br> </br> 

# Medium 레벨

![](https://images.velog.io/images/kmk9502/post/458171e0-867c-46df-9c70-3a3b259b4199/medium%20%EB%A0%88%EB%B2%A8%EC%97%90%EC%84%9C%20%EC%9E%85%EB%A0%A5%EC%B0%BD%20%ED%99%95%EC%9D%B8.png)

Low 레벨과 달리 사용자가 직접 User ID를 입력하는 것이 아닌, 드롭다운 메뉴 형태로 되어있다.
</br> </br> 

![](https://images.velog.io/images/kmk9502/post/37026fbf-59ac-43db-a607-7db497f28dc6/Burp%20Suite%EB%A1%9C%20Medium%20%EB%A0%88%EB%B2%A8%20%ED%8C%A8%ED%82%B7%20%EC%BA%A1%EC%B3%90.png)

사이트에서 입력 값을 쓸 수 없으니 프록시 기반 도구를 활용하여 `요청 패킷을 수정`하여 공격한다.
</br> </br> 

![](https://images.velog.io/images/kmk9502/post/0dc301ca-f694-4a5b-b53c-11ad47978708/id%20%ED%8C%8C%EB%9D%BC%EB%AF%B8%ED%84%B0%EC%97%90%20%EC%B0%B8%20%EA%B0%92%20%EC%82%BD%EC%9E%85%20%ED%9B%84%20Forward.png)

요청 패킷의 id 값에 `1 or 1=1`을 포함시켜 모든 사용자를 확인한다.
</br> </br> 

![](https://images.velog.io/images/kmk9502/post/be0d7a4e-a01d-44ff-9160-0659cd882e30/Medium%20%EB%A0%88%EB%B2%A8%20%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)

공격에 성공하였다. 
</br> </br> 

`union select` 구문도 가능한지 테스트를 해보자.

![](https://images.velog.io/images/kmk9502/post/7a107f31-afc0-46a2-9ade-4dddb5514e81/%ED%94%84%EB%A1%9D%EC%8B%9C%20%EB%8F%84%EA%B5%AC%EB%A1%9C%20union%20select%20%EA%B5%AC%EB%AC%B8%20%EA%B3%B5%EA%B2%A9.png)

기본 요청 값 1 뒤에 `union select` 구문을 삽입해 보자. 구문 내용은 `users 테이블` 내의 사용자 이름과 비밀번호를 출력하는 것이다. 
</br> </br> 

![](https://images.velog.io/images/kmk9502/post/127dccbe-a76d-40d3-81cf-7dbbc0328fbc/Medium%20%EB%A0%88%EB%B2%A8%20union%20%EA%B5%AC%EB%AC%B8%20%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)

Medium 레벨에서 union select 구문 공격이 성공하였다.
</br> </br> 

# High 레벨

![](https://images.velog.io/images/kmk9502/post/720e3311-4e65-4332-b802-ec8167451c00/High%20%EB%A0%88%EB%B2%A8%20%ED%99%94%EB%A9%B4.png)

![](https://images.velog.io/images/kmk9502/post/2c5806d8-5813-459c-bb3a-29d5498a6aed/High%20%EB%A0%88%EB%B2%A8%EC%97%90%EC%84%9C%20%ED%91%9C%EC%8B%9C%EB%90%98%EB%8A%94%20%EB%B3%84%EB%8F%84%EC%9D%98%20%EC%9E%85%EB%A0%A5%20%ED%8E%98%EC%9D%B4%EC%A7%80.png)

![](https://images.velog.io/images/kmk9502/post/79164e17-d966-4a8c-b474-7aac1eb83aee/High%20%EB%A0%88%EB%B2%A8%20%EB%B3%84%EB%8F%84%20%ED%8E%98%EC%9D%B4%EC%A7%80%20%EA%B0%92%20%EC%9E%85%EB%A0%A5%20%ED%9B%84%20%EA%B2%B0%EA%B3%BC.png)

High 레벨에서는 입력 폼 자체가 존재하지 않으며, 해당 링크 클릭 시 별도의 페이지가 열리며 입력 값을 받는다. </br>
또한, 별도의 페이지에서 값을 입력 후 전송하면 원래의 페이지에서 결과가 출력된다.
</br> </br>

![](https://images.velog.io/images/kmk9502/post/b5d3b4c7-5369-4223-9c81-cd441320896b/or%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%9C%20%EA%B2%B0%EA%B3%BC_%EB%8B%A4%EB%A5%B8%20%EB%A0%88%EB%B2%A8%EA%B3%BC%20%EB%8B%A4%EB%A5%B4%EA%B2%8C%201%EA%B0%9C%EB%A7%8C%20%EC%B6%9C%EB%A0%A5.png)

별도의 페이지에서 `1' or '1'='1`을 입력 후 전송한 결과이다. Low와 Medium에서와는 다르게 한 개의 정보만 출력된다.
</br> </br>

위 결과로 쿼리문 뒷부분에 추가 쿼리를 실행하지 못하게 하는 코드가 있다는 것을 추측할 수 있다. </br>
High 레벨의 소스코드를 분석해보자. 

![](https://images.velog.io/images/kmk9502/post/9fd75e3e-92bc-4f80-b73a-bdc27feaefd3/High%20%EB%A0%88%EB%B2%A8%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

위 소스코드에서 ` $query` 부분에 있는 ` $id`를 보면 쿼리문을 담는 곳 뒷부분에 `LIMIT` 구문이 존재하는 것을 확인할 수 있다. </br>
해당 구문을 우회해보자.
 </br> </br>

![](https://images.velog.io/images/kmk9502/post/8062244c-c967-4fc6-9a4a-422a173caa2f/High%20%EB%A0%88%EB%B2%A8%20LIMIT%20%EC%A3%BC%EC%84%9D%20%EC%B2%98%EB%A6%AC%20%ED%9B%84%20%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)

LIMIT 구문을 우회하기 위해 `1' or '1'='1'#`으로 LIMIT 구문을 주석 처리하여 공격이 성공한 것을 확인할 수 있다. 
</br> </br>

![](https://images.velog.io/images/kmk9502/post/92632c75-81b6-46f7-ab7b-ab4511b5ed67/High%20%EB%A0%88%EB%B2%A8%EC%97%90%EC%84%9C%20union%20select%20%EA%B5%AC%EB%AC%B8%20%EC%8B%A4%ED%96%89%20%EC%84%B1%EA%B3%B5.png)

마찬가지로, union select 구문 뒤에 `#`으로 LIMIT 구문을 주석 처리하여 공격할 수 있다.

