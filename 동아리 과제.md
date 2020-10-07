#동아리 과제
# **1. WEB2_HTTP** 
## **① HTTP란?**
 - ### HyperText Transfer Protocol = HTTP
- ### HTTP 구분
    - #### Request (요구)
    - #### Response (응답)
## **② Request message**
- ### 첫번째 행= Request line
    ### ex) GET /1.html HTTP/1.1
    - GET: 웹서버에게 요청하는 정보가 무엇인가
    (데이터를 웹서브로 가져올 때)
 
    - /1.html: 우리가 웹서버한테 요청하는 정보가 무엇인가 
    (1.html에 따라서 웹브라우저가 요청한 정보를 응답해줌)
  - HTTP/1.1: 웹브라우저가 현재 사용하고 있는, 사용할 수 있는 HTTP의 버전이 1.1.이라는 것
 
 - ### 나머지 행 = request headers
   - Host: 인터넷에 연결되어 있는 컴퓨터 한대 한대를 식별하는 이름

   - User-Agent: 웹브라우저의 다른 표현 
   (요청하는 웹브라우저가 어떤 웹브라우저인지 알려줌) 
   - Accept- Encoding: 웹브라우저, 웹서버가 서로 통신할 때 응답하는 데이터가 많으면 압축해서 전송해 웹브라우저가 압축을 풀어서 처리할 수 있어서 네트워크의 자원을 아낄 수 있음
   - If-Modified-Since: 자신이 갖고 있는 파일의 최신의 것을 비교해 전송해줌

## **③Response message**
 ex) HTTP/1.1 200 OK
HTTP/1.1: HTTP/1.1이라는 포멧을 쓰고 있다는 것
200: Status Code (200 ok는 성공했다는 것) <br/>
-> 100번대: 정보를 주기위한 것 <br/> 
     200번대: 성공했다는것 <br/>
    300번대: 다시 작동하게 하는 것 <br/>
    400번대: 클라이언트의 오류<br/>
    500번대: 서버의 오류<br/>
Content-Type: 웹서버 분류
Content-Length: 응답하는 컨텐츠의 사이즈

http는 안전하지 못함 <-> https는 안전함


# **2. Domain Name System**

1. Domain Name System 소개

Domain Name System (DNS)
  호스트의 도메인 이름을 호스트의 네트워크 주소로 바꾸거나
  그 반대의 변환을 수행할 수 있도록 하기 위해 개발
   
  특정 컴퓨터(또는 네트워크로 연결된 임의의 장치)의 주소를 찾기 위해, 
 사람이 이해하기 쉬운 도메인 이름을 숫자로 된 식별 번호(IP 주소)로 변환해 준다. 

2. DNS의 태동
 
Stanford Research Institute
과거에는 이 곳에서 전세계 모든 hosts파일을 관리하였다.
이곳의 hosts 파일을 다운받아 접속할수 있었다.

문제점
Stanford Research Institute에서 hosts파일을 갱신하지 않으면 새로운 파일을 사용하지
 못하였다.
hosts파일 갱신을 수작업으로 하여 많은 시간과 비용이 들어간다.
하나의 파일에 모든 hosts파일이 들어가면 언젠가는 한계가 생긴다.

이에 새로운 시스템이 생기는데 이것이 DNS이다.

3. DNS의 원리

Domain Name System Server (DNS Server)
Domain Name System Server
 도메인의 이름과 도메인의 IP주소를 저장하고 기억해두는 역할을 한다
 
 1. 개인컴퓨터가 DNS Server에 도메인 이름을 물어본다.
 2. DNS Server는 개인컴퓨터에게 도메인이름으로 저장되있는 IP주소를 전달해준다.
 3. 개인 컴퓨터는 받은 IP주소로 접속할수 있다.

 Stanford Research Institute보다 좋은점

 과거는 전화를 걸어 평일에만 IP주소를 받을수 있었지만 현재는 자동화로 빠르고 
자유롭게 받을수 있게 되었다. 
행정결차가 간소화되고, 신속해졌다.
 DNS Server가 IP주소가 변경되는 순간 즉시 모든 사용 컴퓨터는 변경될수 있다.

4. public DNS
  통신사에서 제공하는 DNS

 Google의 public DNS
  8.8.8.8 or 8.8.4.4

5. 도메인 이름의 구조
 
 bog.example.com.

.               Root
com          Top-level
example      Second-level             표작성
blog          sub

Root >>> Top-level>>> Second-level >>> sub

6. 도메인 이름 등록 과정과 원리

ICANN <<< Registry <<<<<< Registrar <<<<< Registrant
                등록소               등록대행자            등록자
 
등록자 >> 등록대행자        도메인주소와 이름을 알려준다
등록대행자 >>> 등록소     등록소는 Top-level domain에 도메인주소와 이름을 저장해둔다

7. nslookup
 
  Name Server lookup (nslookup)
 도메인 네임을 얻거나 IP주소 매핑 또는 다른 특정한 DNS 레코드를 
  도메인 네임 시스템(DNS)에 질의 할때 사용됩니다.

8. DNS record & CNAME

DNS record
  dns서버에 저장하는 도메인의 이름의 정보 한건

A >>   ip주소 (Address)
NS >> 관리 Name Server (Name Server) 
CNAME >> 도메인의 별명 (Canonical Name)


CNAME
  도메인의 별명을 붙여 별명을 입력시 도메인 주소로 변환후 접속하게 해준다.




# **3. Home server**

1. router
-IP address 
 컴퓨터의 인터넷을 통신하기 위해 꼭 필요한 것
 	LAN(Local Area Network) 지역 네트워크
		private ip address: 지역 네트워크에서만 사용할 수 있는 ip address 
 	WAN(Wide Area Network) 전세계에서 가장 거대한 네트워크인 인터넷이라는 것에 조속되어 있음
		public ip address: 광역 네트워크 안에서 공유기와 연결할 수 있게 해주는 ip 
	
 	
	
2. NAT(Network Address Translation) 
- NAT의 역할
     1. private IP address 의 요청을 기록한다.
     2. private IP address 를 public IP address로 변환한다.
     3. 응답 받은 정보를 요청자가 맞는지 확인한뒤 private IP address에게 전달해준다.

3. PORT
 여러 서버들을 어느 것과 상호작용할지를 결정지을 때 사용하는 것이 포트번호이다.

4. Port forwarding
 -컴퓨터들에게 특정 포트를 개방시켜 줌으로써 서로 통신이 되도록 하는 것을 의미한다.
 -외부에서 어떤 서버 혹은 IP로 접속을 하든간에 특정 포트로 접속을 요청하게 되면 무조건 그 서버나 IP로 넘겨버리는 것이라고 할 수 있음
 -NAT의 기능 중 하나이며 포트매핑이라고 불리기도 한다.
 
5. DHCP (Dynamic Host Configuration Protocol)
 동정 호스트 설정 프로토콜이다.
 
- DHCP 동작
	DHCP Request: DHCP 서버에 갱신을 요구하는 Request 패킷을 보낸다. 서버가 이 패킷을 받으면, 2단계로 넘어간다.
	DHCP ACK:  DHCP서버에서 Request를 요청한 클라이언트에게 ACK패킷을 보낸다 이 패킷에는 갱신에 대한 정보가 담겨 있다.
 -역할별 분류	
	 DHCP server
		ip를 보유하고, 원하는 가입자에게 ip를 분배해주는 역할을 한다.
	 DHCP client
		pc,스마트폰, 스마트패드 등 각종 최종 단말 장치들은 모두 탑재되어 있어서 서버로부터 ip를 할당받아 사용한다. 
- 장점
	PC의 수가 많거나 PC 자체 변동사항이 많은 경우 IP설정이 자동으로 되기 때문에 효율적으로 사용 가능하고, IP를 자동으로 할당해주기 때문에 IP 충돌을 막을수 있따.
- 단점
         DHCP 서버에 의존되기 때문에 서버가 다운되면 IP할당이 제대로 이루어지지 않는다.


