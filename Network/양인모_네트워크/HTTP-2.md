저번 글에 이어서 HTTP를 이야기하겠다.
https://velog.io/@jjewqm/Network-Forensics-dik3cj407w

# HTTP method

![메소드.png](https://images.velog.io/post-images/jjewqm/b3e27c40-0fc5-11ea-8fc4-47ad3e214fe0/메소드.png)

# GET

GET은 서버의 데이터를 가져오는 역할을 한다.
URL 에 사이트 주소를 입력하고 확인을 누르면, 브라우저에서 GET 요청으로 서버에 페이지를 요청하고 요청한 페이지 파일을 가져온다.

## GET 예시

![GET.png](https://images.velog.io/post-images/jjewqm/a415e120-0fc6-11ea-8fc4-47ad3e214fe0/GET.png)

### Request Headers

![GET.png](https://images.velog.io/post-images/jjewqm/727302f0-0fc7-11ea-af2a-4d50b1252f23/GET.png)
Request Line은 세가지 요소로 구성된다.

1. 메소드

   - GET, POST, HEAD, PUT 등

2. 요청한 문서 경로

   - URL, 또는 프로토콜, 포트, 도메인의 절대 경로로 나타낸다.
   - origin 형식: 끝에 '?'와 쿼리 문자열이 붙는 절대 경로
     GET, POST, HEAD, OPTIONS 메서드와 함께 사용한다.
     POST / HTTP 1.1
     GET /background.png HTTP/1.0
     HEAD /test.html?query=alibaba HTTP/1.1
     OPTIONS /anypage.html HTTP/1.0

   - absolute 형식 : 완전한 URL 형식
     프록시에 연결하는 경우 대부분 GET과 함께 사용된다.
     ex) https://developer.mozilla.org/ko/docs/Web/HTTP/Messages
   - authority 형식 : 도메인 이름 및 옵션 포트(':'가 앞에 붙음)로 이루어진 URL의 `authority component`이다.
     HTTP 터널을 구축하는 경우에만 CONNECT와 함께 사용한다.
     CONNECT developer.mozilla.org:80 HTTP/1.1
   - asterisk 형식 : `OPTIONS`와 함께 `*` 하나로 간단하게 서버 전체를 나타낸다. ex) OPTIONS \* HTTP/1.1

3. HTTP 버전

### Request 주요 헤더필드

`HOST` : 리퀘스트를 받은 서버의 URL
`User-Agent` : 클라이언트 소프트웨어의 명칭이나 버전 정보를 의미
예시의 클라이언트는 크롬 브라우저, Windows NT 10.0을 사용한다.
`Accept-Encoding` : 클라이언트가 `Content-Encoding`으로 받은 인코딩방식 주로 데이터압축을 나타낸다.
`if-Unmodified-since `: 클라이언트 파일과 서버의 파일과 비교해 최신파일이 아니면 최신 파일을 보내주고 최신파일이면 보내지 않는다.

메시지 헤더 이후에는 공백 행이 오고 그 뒤에 송신할 데이터가 위치한다.
이 부분이 메시지 본문이며 메시지의 실제 내용이다.
`GET`은 `URI`와 메소드만으로 서버가 무엇을 할지 판단하므로 본문을 작성하지 않는다.
`POST`는 폼에 입력한 데이터들을 본문에 작성한다.

## Response header

HTTP 응답의 시작 줄은 상태 줄(status line)이라고 불리며, 아래 정보를 가진다.

### HTTP/1.1 200 OK

- 프로토콜 버전
  보통 HTTP/1.1입니다.
- 상태 코드
  요청의 성공 여부를 나타냅니다. 200, 404 혹은 302입니다.
- 상태 텍스트
  짧고 간결하게 상태 코드에 대한 설명을 글로 나타내어 사람들이 HTTP 메시지를 이해할 때 도움이 됩니다.

다양한 종류의 응답 헤더가 있는데, 이들은 몇몇 그룹으로 나뉜다.

- General 헤더
  Via와 같은 헤더는 메시지 전체에 적용된다.
- Response 헤더
  Vary와 Accept-Ranges와 같은 헤더는 상태 줄에 미처 들어가지 못했던 서버에 대한 추가 정보를 제공한다.
- Entity 헤더
  Content-Length와 같은 헤더는 요청 본문에 적용된다.
  요청 내에 본문이 없는 경우 entity 헤더는 전송되지 않는다.
  ![Response 헤더.png](https://images.velog.io/post-images/jjewqm/0f7f4f70-0fcf-11ea-be26-0b15ff12ee7e/Response-헤더.png)

요청 페이지가 문장, 영상, 이미지 등으로 구성되어 있다면 각각의 리퀘스트 메시지를 보낸다.
리퀘스트에 쓰는 URI는 1개 만으로 결정되어 한 번에 파일 한개 씩 읽어야 한다.
만약 페이지에 문장과 영상이 3개 존재하면 총 4번의 리퀘스트 메시지를 보내야 한다. 그럼 웹 서버는 4번의 리퀘스트 메시지에 대한 4번의 응답 메시지를 보낸다.

![URI는 한개씩.png](https://images.velog.io/post-images/jjewqm/68fef380-0fce-11ea-b767-7979935629b8/URI는-한개씩.png)

그림에서 보듯이 html문서, 이미지 파일, JS 파일 각각 따로 응답한 걸 알 수 있다.

---

## reference

본 글은 성공과 실패를 결정하는 1%의 네트워크 원리를 정리합니다.
https://opentutorials.org/course/3385
https://joshua1988.github.io/web-development/web-protocols/
https://developer.mozilla.org/ko/docs/Web/HTTP/Messages
https://gmlwjd9405.github.io/2019/04/17/what-is-http-protocol.html
