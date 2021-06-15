# Section 07
## 37강
- 네트워크 스니핑
    - 네트워크 트래픽 도청
    - 대표 패킷 애널라이저
        - Wireshark
        - tcpdump
    - 정보 수집
    - 서비스 분석
    - 사용자 계정 정보 탈취

## 38강
![화면 캡처 2020-11-19 123124](https://user-images.githubusercontent.com/64259087/99618027-ececc180-2a63-11eb-81ba-a0c366144770.png)
- wireshark 실행

![화면 캡처 2020-11-19 123228_LI](https://user-images.githubusercontent.com/64259087/99618113-173e7f00-2a64-11eb-9d95-dcc3aa7fa443.jpg)
- 사설 네트워크 트래픽인 eth1을 캡쳐 실행

![화면 캡처 2020-11-19 123544](https://user-images.githubusercontent.com/64259087/99618122-1dccf680-2a64-11eb-86ec-71bd99f4f2fe.png)

# 39강
- 중간자 공격 = MIMT (Man In The Middle attack)

![화면 캡처 2020-11-19 131122](https://user-images.githubusercontent.com/64259087/99625056-b2d6ec00-2a72-11eb-88d9-a29a3d8bc98d.png)
- arpspoof 명령어를 이용해서 arp 스푸핑을 할 수 있음.
- ip forward의 값을 1로 변경해야 함

![화면 캡처 2020-11-19 131303](https://user-images.githubusercontent.com/64259087/99625088-c84c1600-2a72-11eb-86c4-7bc10ffc5ed4.png)
- 192.168.56.102 -> 메타스플로잇테이블 ip 192.168.56.101 -> 칼리 리눅스 ip
- 반대로 arpsnoof -i eth1 -t 192.168.56.101 192.168.56.102로 입력했을경우 오류 발생.

![화면 캡처 2020-11-19 133736](https://user-images.githubusercontent.com/64259087/99625754-4230cf00-2a74-11eb-8b65-679dfbbd01c0.png)

![화면 캡처 2020-11-19 133626](https://user-images.githubusercontent.com/64259087/99625213-195c0a00-2a73-11eb-9c1b-ef861f6fcd66.png)
- 다음과 같은 명령어로 오류 해결
- 칼리가 라우터 같은 역할을 하는 것인데 그 전의 명령어 같은 경우 칼리와 메타스플로잇테이블이 서로 정보를  주고 받는 것. 즉, 칼리리눅스가 메타스플로잇테이블과 윈도우 운영 체제의 라우터의 역할로 중간자 공격을 해야하는 것인데 윈도우 운영체제의 ip주소가 들어가야할 명령어에 칼리리눅스 ip주소가 입력됨.
- 192.168.56.102 -> 메타스플로잇테이블 192.168.56.103 -> 윈도우 운영 체제

![화면 캡처 2020-11-19 133713_LI](https://user-images.githubusercontent.com/64259087/99625717-30e7c280-2a74-11eb-8bdd-b5c908bfee4d.jpg)

