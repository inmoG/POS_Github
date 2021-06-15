# 문제

우리는 북한이 내년 타이틀전을 치루고 있음을 알 수 있다. Kim Ill-song은 우리가 찾고 있는 사람 일 것입니다. 우리는 Kim Ill-song의 네트워크 트래픽을 포착했으며 다른 국가의 많은 사람들과 의사소통을 하고 있습니다. 우리는 그가 뇌물을 줬다고 생각하는데 증거가 필요합니다. 현금은 상대적으로 이동하기 쉽지만, 뇌물 중 하나가 다른 것임을 알게 되었습니다. 곧 호스팅 도시에 대한 투표가 시작됩니다. 이 폴더에 있는 Round 2 패킷 캡처를 사용하여 사례에 대해 자세히 알아보고 다음 질문에 답하십시오. **어떤 도시 관리가 뇌물을 받고 있습니까?**

Hint : 인코딩

---

![defcon 22 #2.png](https://images.velog.io/post-images/jjewqm/76ec3c80-0b89-11ea-be29-f571dc8d24b5/defcon-22-2.png)

패킷을 확인하니 IRC 프로토콜 통신흔적이 있다.

_IRC : 인터넷 채팅 프로토콜이자 이 프로토콜을 사용하는 채팅 서버 및 클라이언트 소프트웨어. 소셜 네트워크의 시초라 할 수 있다._

IRC프로토콜은 채팅 프로토콜이니 분석해볼 필요가 있다. follow - TCP Stream 기능을 사용해 분석하겠다.

![20191120_205339.png](https://images.velog.io/post-images/jjewqm/751ec820-0b8c-11ea-ab7d-d93b128a9cd6/20191120205339.png)

분석 결과 패킷의 데이터들이 Base64로 인코딩 되어있다.
해당 데이터들을 디코딩하겠다.

# Base64 디코딩

![defcon 22 #2-3.png](https://images.velog.io/post-images/jjewqm/3f7671d0-0b8e-11ea-ab7d-d93b128a9cd6/defcon-22-2-3.png)

## 결과

![defcon 22 #2-4.png](https://images.velog.io/post-images/jjewqm/4376c460-0b8e-11ea-ab7d-d93b128a9cd6/defcon-22-2-4.png)

### Base32 디코딩

![defcon 22 #2-5.png](https://images.velog.io/post-images/jjewqm/91e7a380-0b8e-11ea-ab7d-d93b128a9cd6/defcon-22-2-5.png)

하지만 여전히 알 수 없는 값으로 디코딩 되어있어 html, url, base32으로 한번 더 디코딩했다. 그 결과 **base32**으로 디코딩 해 채팅내역을 확인하였다.

# Base64 디코딩

![defcon 22 #2-6.png](https://images.velog.io/post-images/jjewqm/4b4a4990-0b8f-11ea-a6a4-f18ec5ff5eba/defcon-22-2-6.png)

## Base32 디코딩

![defcon 22 #2-7.png](https://images.velog.io/post-images/jjewqm/6fd6fa10-0b8f-11ea-a6a4-f18ec5ff5eba/defcon-22-2-7.png)

채팅한 데이터들을 계속 base64 👉 base32 디코딩한 결과  
**JEQGGYLOEBRGKIDJNYQGGOLGME2WEODDMIZWEMJZG5QWKNLDMU2GEYLGHA2DCNLBGM3TKYRAO5UXI2DJNYQHI2DFEB3WKZLLFY======**
해당 문자열에서 암호화된 문자열을 추출했다.
암호화된 문자열은 MD5 해쉬 알고리즘을 쓴 것으로 추측된다
_# 32개의 문자열로 MD5 알고리즘 추측_

![defcon 22 #2-8.png](https://images.velog.io/post-images/jjewqm/113c6bb0-0b90-11ea-a6a4-f18ec5ff5eba/defcon-22-2-8.png)

MD5 복호화 사이트로 크랙결과 caracas 문자열을 획득했다.
Caracas는 베네수엘라의 수도며 Caracas 도시에서 뇌물을 받았다는 걸 알 수 있다.

### KEY

**Caracas**

---

본 글은 http://www.ctf-d.com/challenges 문제를 풀이합니다.
