# TCP header

- 각 플래그마다 의미하는 바가 달라 통신상에서 비트의 설정으로 의미를 부여
- Port Scan과 같은 공격 유형 판별 시 중요한 정보를 제공한다.

|        플래그        |                                        설명                                        |
| :------------------: | :--------------------------------------------------------------------------------: |
| SYN(Synchronization) |                              초기 세션 설정에 사용 됨                              |
| ACK(Acknowledgement) |                                  SYN에 대한 응답                                   |
|     FIN(Finish)      |                         세션을 종료시키는데 사용(정상종료)                         |
|      RST(Reset)      |                  재설정(Reset)을 하는 과정에서 사용(비정상 종료)                   |
|      PSH(Push)       | 대화형 트래픽에 사용되는 것으로 버퍼가 채워지기를 기다리지 않고 데이터를 바로 전달 |
|     URG(Urgent)      |                              긴급 데이터 전송 플래그                               |

## TCP 3-Way HandShaking

네트워크 통신연결의 시작이다.
TCP/IP프로토콜을 이용해서 통신을 하는 응용프로그램이 데이터를 전송하기 전에 정확한 전송을 보장하고자 상대방 컴퓨터와 사전에 세션을 수립하는 과정을 의미한다.

![3-way.png](https://images.velog.io/post-images/jjewqm/3dd58810-0e78-11ea-8b32-2f04ff68d3d7/3-way.png)

### TCP 3-way Handshaking 역할

• 클라이언트와 서버가 데이터 전송 준비가 되었다는 것을 보장하고, 실제로 전달이 시작되기 전에 다른 쪽이 준비된 것을 알린다.

• 양쪽 모두 상대편에 대한 초기 순차일련변호를 얻을 수 있다.

#### 3-way Handshaking 과정

**[STEP 1]**

클라이언트는 서버에 접속을 요청하는 SYN 패킷을 보낸다. 클라이언트는 SYN/ACK 응답을 기다리는 SYN_SENT 상태가 된다.

**[STEP 2]**

서버는 SYN 요청을 받고 클라이언트에게 요청을 수락한다는 ACK 와 SYN flag 패킷을 발송한다. 서버는 클라이언트가 ACK 패킷으로 응답하기를 기다린다.
이때 서버는 SYN_RECEIVED 상태가 된다.

**[STEP 3]**

클라이언트는 서버에게 ACK 패킷을 보내 데이터 송수신 상태, 즉 ESTABLISHED 상태가 된다.

이 방식이 신뢰성 있는 연결, TCP 3-Way handshake 방식이다.

### TCP 4-way Handshaking 역할

**3-Way handshake**는 TCP의 **연결을 초기화** 할 때 사용한다면,
4-Way handshake는 세션을 종료하기 위해 수행되는 절차이다.

![4-way.png](https://images.velog.io/post-images/jjewqm/4576a810-0e78-11ea-8b32-2f04ff68d3d7/4-way.png)

#### TCP 4-way Handshaking 과정

**[STEP 1]**

클라이언트가 연결을 종료하겠다는 FIN플래그를 전송한다.

**[STEP 2]**

서버는 확인메시지를 보내고 자신의 통신이 끝날때까지 기다린다.

**[STEP 3]**

서버가 통신이 끝났으면 연결이 종료되었다고 클라이언트에게 FIN 패킷을 전송한다.

**[STEP 4]**

클라이언트는 확인 메시지를 보낸다.

그런데 서버가 FIN을 전송하기 전에 전송한 ACK 패킷이 Routing 지연이나 패킷 유실로 인한 재전송으로 FIN 패킷보다 늦게 도착할 수 있다.

클라이언트가 세션을 종료하고 뒤늦게 패킷이 도착하면 데이터가 유실된다.

이러한 현상에 대비하여 클라이언트는 서버로부터 FIN을 수신하더라도 일정시간(디폴트 240초) 동안 세션을 남겨놓고 잉여 패킷을 기다린다. 이 과정을 `TIME_WAIT` 라고 부른다.

---

출처: https://mindnet.tistory.com/entry/네트워크-쉽게-이해하기-22편-TCP-3-WayHandshake-4-WayHandshake?category=702276 [Mind Net]
https://mygumi.tistory.com/139
