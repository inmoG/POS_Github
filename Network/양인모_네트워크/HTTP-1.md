# 접속의 시작 : URL 입력부터

인터넷에 접속하기 위해 가장 먼저 할 일은 브라우저에 URL을 입력하는 것이다.

## URL (Uniform Resource Locator)

네트워크 상에서 자원이 어디 있는지를 알려주기 위한 경로이며 http://, ftp:, file:, mailto: 등의 형식을 사용한다.

브라우저 : 웹서버에 접속하는 기능, 파일 업로드 기능, 메일 송수신 기능 등을 가지고 있는 복합적인 클라이언트 소프트웨어

그림[1-1]

모든 URL은 **http:, ftp:, file:, mailto:** 부분에서 엑세스 방법을 나타낸다.
엑세스 대상이 웹 서버라면 **HTTP**프로토콜을 사용하고 FTP 서버라면 **FTP**프로토콜을 사용한다.
_# 엑세스 할 때 네트워크를 사용하지 않는 것도 있어 프로토콜을 나타낸다 생각하면 안된다. 엑세스 방법의 종류라 생각해야 한다._

## URL 해독

URL을 입력하면 브라우저는 웹 서버에 보내는 리퀘스트 메시지를 작성하기 위해 URL을 해독한다.

### URL 요소

**http://www.lab.cyber.co.kr/dir1/file1.html**
⬇
**protocol://computer_name:port/directory_name/document_name?parameters**
⬇
**protocol:** + **//** + **computer_name:port** + **/** + **directory_name** + **/** + **document_name?parameters**

protocol : 문서를 접근하기 위해 사용하는 프로토콜 이름
computer_name : 문서가 있는 컴퓨터(서버)의 도메인 이름
port : 서버가 어떤 포트 숫자를 바라보고 있는지 (생략 가능)
document_name : 서버 컴퓨터에 있는 특정 문서의 이름
parameters : 페이지에 넘기는 변수 (생략 가능)

**http://www.lab.cyber.co.kr/dir1/file1.html**
위 URL의 의미는 아래와 같다.

1. http 프로토콜을 이용해서
2. www.lab.cyber.co.kr 도메인 명을 가진 서버에 접속한다.
3. 접속한 서버에 **dir1 디렉토리**의
4. **file1.html**파일을 엑세스한다.

#### 파일명을 생략한 경우

**http://www.lab.cyber.co.kr/dir/**
URL 끝이 **" / "** 로 끝나는 것은 **/dir/** 다음에 써야 할 파일명을 생략한다는 의미다.
파일명을 생략하면 브라우저는 어느 파일에 엑세스해야 할 지 모른다.
이런 경우를 대비해 **'index.html', 'default.html'** 이름의 파일을 미리 서버에 설정해둔다.

![index.html1.png](https://images.velog.io/post-images/jjewqm/c16b7a60-0e8f-11ea-948d-5ba9629ecf51/index.html1.png)

https://www.naver.com/ URL을 이용해 네이버에 접속하면 **index.html** 파일이 생략되어있다.

![index.html2.png](https://images.velog.io/post-images/jjewqm/b798fb70-0e8f-11ea-948d-5ba9629ecf51/index.html2.png)

생략된 **index.html**을 추가해도 문제없이 네이버에 접속할 수 있다.
URL 끝의 **/**를 생략해 접속해도 문제없다. _# https://www.naver.com_
**/** 는 루트디렉토리를 의미하며 **'index.html', 'default.html'** 이름의 파일이 미리 설정되었기 때문이다.

# HTTP

- HTTP는 서버와 클라이언트가 인터넷상에서 데이터를 주고받기 위한 프로토콜(protocol)이다.

## 작동방식

![http 원리.png](https://images.velog.io/post-images/jjewqm/ba3660d0-0eca-11ea-a710-73066240b450/http-원리.png)

### 특징

- 비연결 지향(Connectionless)
  클라이언트가 request를 서버에 보내고, 서버가 클라이언트에 요청에 맞는 response를 보내면 바로 연결을 끊는다.
- 무상태(Stateless)
  연결을 끊는 순간 클라이언트와 서버의 통신은 끝나며 상태 정보를 유지하지 않는다.

### 장점

- 불특정 다수를 대상으로 하는 서비스에는 적합하다.
- 클라이언트와 서버가 계속 연결된 형태가 아니기 때문에 클라이언트와 서버 간의 최대 연결 수보다 훨씬 많은 요청과 응답을 처리할 수 있다.

### 단점

- 연결을 끊어버리기 때문에, 클라이언트의 이전 상황을 알 수가 없다.
- 이러한 특징을 무상태(Stateless)라고 말한다.
- 이러한 특징 때문에 정보를 유지하기 위해서 Cookie와 같은 기술을 사용한다.

---

쿠키와 세션은 아래 링크를 참조바랍니다.
https://doooyeon.github.io/2018/09/10/cookie-and-session.html
https://jeong-pro.tistory.com/80
https://www.youtube.com/watch?v=1emZgLiGE4s&list=WL&index=2&t=2s

## HTTP Request

클라이언트(브라우저)는 서버에게 **Request** 메시지를 보낸다.
Request 메시지 내부에는 **'무엇을', '어떻게 해서'** 라는 내용이 쓰여져 있다.
**'무엇을'**에 해당하는 것을 **URI**라 하고 **'어떻게 해서'** 에 해당하는 것은 메소드라 부른다. 이 메소드를 사용해 웹 서버에 어떤 동작을 할 것인지 전달한다.

### 대표 Method

- **GET** : 문서를 요청. 서버가 클라이언트에 상태 정보와 복제된 문서를 보냄으로써 응답을 함. (조회)
- **HEAD** : 상태 정보를 요청. GET 과 동일한 형태로 응답을 하지만, 문서를 복제하지는 않는다.
- **POST** : 데이터를 서버로 송신. 서버는 해당 데이터를 특정 아이템에 덧붙인다. (생성)
- **PUT** : 데이터를 서버로 송신. 서버가 특정 아이템을 완전히 대체한다. (수정)

## HTTP Response

**request** 메시지를 받은 서버는 메시지를 해독해 **URI**와 **Method** 요구사항을 처리한다.
그런 다음 **Response** 메시지에 **Status Code(상태 코드)**를 첨부해 클라이언트에게 전송한다.
**Response** 메시지를 받은 클라이언트는 데이터를 추출해 화면에 표시하면 HTTP의 동작이 끝난다.

### Status Code(상태 코드)

- 응답 메시지의 맨 앞부분에 존재한다.
- 실행 결과가 정상 종료되었는지, 이상이 발생했는지 나타냄
- 처리한 데이터 결과를 나타내는 코드

**Status Code**는 5개의 클래스(분류)로 구분하며 코드의 첫 번째 숫자는 응답 클래스를 정의한다.

- 1xx (정보): 요청을 받았으며 프로세스를 계속한다
- 2xx (성공): 요청을 성공적으로 받았으며 인식했고 수용하였다
- 3xx (리다이렉션): 요청 완료를 위해 추가 작업 조치가 필요하다
- 4xx (클라이언트 오류): 요청의 문법이 잘못되었거나 요청을 처리할 수 없다
- 5xx (서버 오류): 서버가 명백히 유효한 요청에 대해 충족을 실패했다

Status Code의 더 많은 정보를 원하면 아래 링크를 참조바랍니다.
https://ko.wikipedia.org/wiki/HTTP_상태코드
https://ko.wikipedia.org/wiki/HTTP

---

# reference

성공과 실패를 결정하는 1%의 네트워크 원리 (이도희 역)
https://www.edwith.org/boostcourse-web/lecture/16661/
https://ko.wikipedia.org/wiki/HTTP_상태코드
https://ko.wikipedia.org/wiki/HTTP
https://doooyeon.github.io/2018/09/10/cookie-and-session.html
https://jeong-pro.tistory.com/80
https://joshua1988.github.io/web-development/web-protocols/#http-hyper-text-transfer-protocol
https://ko.wikipedia.org/wiki/URL
https://gmlwjd9405.github.io/2019/04/17/what-is-http-protocol.html
