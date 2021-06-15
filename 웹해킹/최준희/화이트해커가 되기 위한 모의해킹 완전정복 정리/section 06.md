# Section 06
## 27강
- 액티브 스캐닝
    - 공격대상을 직접 스캐닝
    - 액티브 스캐닝 단계부터는 허가가 반드시 필요함 (주의: 허가없이 스캐닝할 경우 불법으로 간주됨)
- 액티브 스캐닝 기법
    - DNS 정보수집
    - 포트 스캐닝
    - 웹 스캐닝
    - 종합 취약점 스캐닝
## 28강
- **DNS 정보수집**
    - 도메인 이름을 ip주소로 변경하기 위해 사용함
    - host (도메인명) : dns 정보를 알아내는 간단한 명령어 (ip,서버 주소 등)
    - nslookup (도메인명) : dns 정보를 알아내는 간단한 명령어
    - host -t ns (도메인명) : **네임서버**를 알아내는 명령어
    - host -l (도메인명) (네임서버명) : 서브도메인과 ip를 알아내는 명령어
    - dnsenum -h : dnsenum 옵션
    - dnsenum (도메인명) : dns 정보 수집
- **host 명령어 옵션**

 - -a

 -t ANY와 같은 기능

 -  -d

 디버깅 모드로 출력

 - -l

 zone 아래 모든 시스템을 출력

 - -r

 반복 처리를 안 함

 - -t

 type을 지정하여 정보를 얻음

 (A:호스트 ip주소, NS:검색한 호스트의 네임 서버 호스트명, PTR:도메인 네임 포인터, ANY:타입의 모든 정보)

 - -w

 DNS 서버의 응답을 기다림

 - -v

 자세한 정보 출력
## 29강
- ping : 어떤 호스트가 살아있는지 알아내는 간단한 명령어
- fping -h : fping의 옵션 확인 명령어
## 30강
- 포트스캐닝
    - 공격 대상 호스트의 어떤 포트가 열려있는지 어떤 서비스가 운영되고 있는지 알아내는 기법
## 31강
- **Nmap**</br>
**주로 사용하는 명령어**
- -sL : 리스트 스캔 (빠른속도로 목적 네트워크 대역의 살아있는 호스트들을 보여줌)
- -sn : 핑 스캔 (목적지 네트워크 대역에 핑을 날려 응답이 있는 호스트만 보여줌)
- -Pn : 핑에 대한 응답이 있는 호스트만 살아있다고 판단하는게 아니라, 해당 호스트가 핑 응답이 없더라도 계속해서 스캔을 해서 살아있는지 확인함
- -sT : 일반적인 TCP 방식을 이용한 포트 스캔
- -sS : 스텔스 TCP 포트 스캔
- -sN/-sF/-sX : 차례대로 TCP Null, Fin, Xmas 스캔
- -sU : 일반적인 UDP 방식을 잉용한 포트 스캔 (매우 느림/오류가 많음)
- -sV : 대상 호스트의 운영체제와 각 포트별 버전을 알아냄
- -p : 포트를 지정하여 해당 포트가 열려있는지 스캔
- -f : 스캔 패킷 차단 방지를 우회할 수 있도록 패킷을 단편화하여 스캔
- -S : 가짜 IP를 사용
- -O : 대상 호스트의 운영체제를 알아냄
- -A : -sV와 비슷하지만 더 많은 정보를 보여줌
- -v : 검색 결과를 좀 더 상세하게 출력 (-vv일경우 더 상세함)

![화면 캡처 2020-11-13 201406](https://user-images.githubusercontent.com/64259087/99069216-4a5eb980-25f1-11eb-9c08-6b17a90586eb.png)
- nmap -sn 192.168.56.1/24 명령어로 목적지 네트워크 대역에 핑을 날려 응답이 있는 호스트만 보여줌. 현재 192.168.56.1 / 192.168.56.100 / 192.168.56.101로 3가지가 나옴.</br>

![화면 캡처 2020-11-13 205210](https://user-images.githubusercontent.com/64259087/99069675-2bacf280-25f2-11eb-9ff4-b9ca17e1f26e.png)
- 강의 진행에 있어서 현재와 같은 옵션 없이 nmap 192.168.56.101을 입력시 열린 포트가 보여지지않음. **(강의 진행에서는 포트 번호가 나열되야함.)**

### 오류 해결

![화면 캡처 2020-11-13 201615](https://user-images.githubusercontent.com/64259087/99069882-89d9d580-25f2-11eb-9efb-4650108c32f7.png)
- 메타스플로잇테이블 실행

![화면 캡처 2020-11-13 201444](https://user-images.githubusercontent.com/64259087/99069923-9f4eff80-25f2-11eb-80c2-3df7991f7444.png)
- 메타스플로잇테이블 실행 후에 nmap -sn 192.168.56.1/24 명령어 입력시 또 하나의 핑을 스캔함. 아마 메타스플로잇테이블의 핑으로 생각됨.

![화면 캡처 2020-11-13 205937](https://user-images.githubusercontent.com/64259087/99070224-2c925400-25f3-11eb-8d94-664df098b67c.png)
- nmap 192.168.56.102 명령어 입력시 포트 번호가 나열되면서 강의를 원활히 진행함.

![화면 캡처 2020-11-13 212202](https://user-images.githubusercontent.com/64259087/99071887-5436eb80-25f6-11eb-888c-1ac401cb1baf.png)
- nmap -sU 192.168.56.102 -p 110-140 명령어 입력으로 포트 번호를 지정함. 110~140 사이의 포트를 스캔함.

![화면 캡처 2020-11-13 212559](https://user-images.githubusercontent.com/64259087/99072168-d7f0d800-25f6-11eb-9c5f-200a8bf84e79.png)
- 명령어 -O를 이용해서 운영 체제를 스캔함. 해당 서버의 운영체제가 리눅스라는 걸 알아냄.

![화면 캡처 2020-11-13 212827](https://user-images.githubusercontent.com/64259087/99072341-3027da00-25f7-11eb-8cfc-cb4c5dbdb70d.png)
- 명령어 -sV를 이용해서 해당 서버의 서비스의 버전을 스캔함.
- -A를 이용하면 더욱 자세한 정보을 알아낼 수 있음.

## 32강
- smtp-user-enum -h : smtp 명령어 옵션

![화면 캡처 2020-11-14 095656](https://user-images.githubusercontent.com/64259087/99134161-fd65fc00-265f-11eb-8e3e-a2ced220948f.png)
- smtp-user-enum -M VRFY -U /usr/share/wordlists/metasploit/namelist.txt -t 192.168.56.102 명령어로 -M VRFY 명령어로 **모드**를 설정하고 -U /usr/share/wordlists/metasploit/namelist.txt 명령어로 스캔할 파일을 설정하고 -t 192.168.56.102로 스캔할 서버 호스트를 설정해서 다음과 같이 스캔결과를 출력.
- -M	: 모드 선택(VRFY , EXPN , RCPT)
- -u	: 사용자가 있는지 체크
- -U	: username에 대한 파일
- -t	: smtp가 실행중인 호스트 IP

## 33강
- nikto -Help : nikto 옵션 명령어

![화면 캡처 2020-11-14 102930](https://user-images.githubusercontent.com/64259087/99135204-9139c700-2664-11eb-9a69-839a266477e2.png)
- nikto -h 192.168.56.102 명령어로 서버 버전이나 php 버전 등 각종 정보를 수집할 수 있음. phpinfo.php와 doc에 관하 내용이 보이는데 사이트에 접속을 하면 정보를 수집할 수 있음.

![화면 캡처 2020-11-14 103036](https://user-images.githubusercontent.com/64259087/99135270-deb63400-2664-11eb-97f3-7f789fb2c2df.png)
- 192.168.56.102/phpinfo.php 사이트에 접속을 해서 php에 관한 정보를 수집할 수 있음.

![화면 캡처 2020-11-14 103108](https://user-images.githubusercontent.com/64259087/99135354-2f2d9180-2665-11eb-9098-7c3180d157df.png)
- 192.168.56.102/doc/ 사이트에 접속을 해서 파일에 접근을 할 수 있음. (굉장히 취약함)

![화면 캡처 2020-11-14 103834](https://user-images.githubusercontent.com/64259087/99135430-921f2880-2665-11eb-96e0-e72748787bbd.png)
- 192.168.56.102/doc/ 사이트에 접속을 해서 파일에 접근을 방지하려면 vi /etc/apache2/apache2.conf 명령어로 입력을 해서 내려보면 빨간색으로 표시되어있는 Indexes를 지우면 해결됨.

## 34강
- sparta 사용법

![화면 캡처 2020-11-18 114508](https://user-images.githubusercontent.com/64259087/99477129-391d0080-2995-11eb-9919-66033c66de22.png)

![화면 캡처 2020-11-18 114551](https://user-images.githubusercontent.com/64259087/99477171-4cc86700-2995-11eb-9565-000a6172252e.png)

![화면 캡처 2020-11-18 114609](https://user-images.githubusercontent.com/64259087/99477204-5c47b000-2995-11eb-8acc-9827c1f68515.png)
- 스캐닝할 ip를 입력
- Run nmap host discovery 옵션 : 네트워크 범위 전체를 검색하였을 때 호스트 검색을 하는 옵션
- Run staged nmap scan 옵션 : 포트가 검색되었을 때 각 포트에 대해서 추가 정보 수집을 하는 옵션

![화면 캡처 2020-11-18 115116](https://user-images.githubusercontent.com/64259087/99477221-67024500-2995-11eb-9ba8-5b0a71213707.png)

![화면 캡처 2020-11-18 115141](https://user-images.githubusercontent.com/64259087/99477239-6f5a8000-2995-11eb-8a7f-b789fa67257e.png)

![화면 캡처 2020-11-18 120021](https://user-images.githubusercontent.com/64259087/99477325-a597ff80-2995-11eb-95bc-0670b1f74418.png)

![화면 캡처 2020-11-18 115544](https://user-images.githubusercontent.com/64259087/99477383-bea0b080-2995-11eb-8dce-73208be4ea39.png)
- 현재 root 계정이 사용중인걸 알아 내면 바로 사용가능.

![화면 캡처 2020-11-18 115608](https://user-images.githubusercontent.com/64259087/99477484-ed1e8b80-2995-11eb-8f1e-ccbe69980b80.png)
- mysql -h 192.168.56.102 -u root 명령어로 root 계정으로 mysql로 접속해서 정보 수집 가능.

## 35강 - 36강
- 종합 취약점 스캐닝
- Nessus 설치법
- Google에 download nessus 검색

![화면 캡처 2020-11-18 122924](https://user-images.githubusercontent.com/64259087/99480808-3245bc00-299c-11eb-8e96-962135740c62.png)
- 해당 사이트에서 32비트면 위에 걸 다운로드 64비트면 아래 걸 다운로드 함. (현재 칼리리눅스 64비트)

![화면 캡처 2020-11-18 123013](https://user-images.githubusercontent.com/64259087/99480874-4e495d80-299c-11eb-8181-decbd94181ea.png)
- 무료버전을 다운로드 (맨 왼쪽)

![화면 캡처 2020-11-18 123037](https://user-images.githubusercontent.com/64259087/99480893-5a351f80-299c-11eb-8a42-91906f5ada7e.png)
- 이름과 이메일을 쓰고 다운로드 코드를 받음. (이메일로 들어가면 코드를 발급받음.)

![화면 캡처 2020-11-18 123154](https://user-images.githubusercontent.com/64259087/99480965-79cc4800-299c-11eb-822b-9ddf8d2af1bc.png)
- 해당 폴더로 들어가면 Nessus 파일이 있는 것이 확인됨.

![화면 캡처 2020-11-18 123408](https://user-images.githubusercontent.com/64259087/99481015-96688000-299c-11eb-8f8e-2af2d73b761d.png)
- cd /root/Downloads/ 로 들어가고 dpkg -i ./Nessus-8.12.1-debian6_amd64.deb 명령어를 입력

![화면 캡처 2020-11-18 125627](https://user-images.githubusercontent.com/64259087/99481452-87ce9880-299d-11eb-92a0-64feffad56e7.png)
- /bin/systemctl start 입력하면 too few arguments 라는 입력이 나옴. (너무 많은 인수)
- /bin/systemctl start nessus. service 입력하면 오류나옴.
- /bin/systemctl start nessus.service 입력하면 아무것도 출력되지 않음.
- /bin/systemctl nessusd start 입력하면 unkown operation nessusd 입력이 나옴. (nessusd 알수 없는 작업)
- 강의 진행에 있어서 nessus가 실행이 되고 위에 8854포트가 열려야 함.
- 애초에 다른 문자열이 나왔지만 강의는 32비트를 다운로드 하였고 자신의 컴퓨터는 64비트를 다운로드 하여 다르다고 판단됨.

![화면 캡처 2020-11-18 125331](https://user-images.githubusercontent.com/64259087/99481898-776aed80-299e-11eb-9e4c-c228c6a998e9.png)
- 원하는 명령어가 나오지 않았지만 혹시나 localhost:8834 사이트로 들어갔을 때 포트가 열려있고 사이트에 접속이 가능함.

- 혹여나 nessus 아이디와 비밀번호를 잊었을 경우 아래와 같이 실행
![화면 캡처 2020-11-18 180434](https://user-images.githubusercontent.com/64259087/99510286-3983be80-29ca-11eb-8f30-34bff2b7123f.png)
- cd /opt/nessus/sbin 폴더로 이동
- ./nessuscli lsuser 명령어로 아이디 확인가능
- ./nessuscli chpasswd 명령어로 비밀번호 변경 가능.

![화면 캡처 2020-11-18 180813](https://user-images.githubusercontent.com/64259087/99510517-85366800-29ca-11eb-9052-9d2cc1fd0000.png)
- nessus 로그인 후 new scan 클릭

![화면 캡처 2020-11-18 180905](https://user-images.githubusercontent.com/64259087/99510591-9aab9200-29ca-11eb-9efa-b43dbd7b14d1.png)

![화면 캡처 2020-11-18 180942](https://user-images.githubusercontent.com/64259087/99510618-a4cd9080-29ca-11eb-8493-5dfe297084dd.png)
- 이름과 타겟을 입력 후 save

![화면 캡처 2020-11-18 181007](https://user-images.githubusercontent.com/64259087/99510702-b9aa2400-29ca-11eb-8143-67830a32c2f1.png)
- 스캔 실행

![화면 캡처 2020-11-18 181410](https://user-images.githubusercontent.com/64259087/99510736-c3338c00-29ca-11eb-9939-0492e343631e.png)
- 스캔을 하면 현재와 같이 취약점들이 나옴

![화면 캡처 2020-11-18 181429](https://user-images.githubusercontent.com/64259087/99510776-cdee2100-29ca-11eb-99af-05b3cfa7b308.png)
- 해당 취약점은 vcn 비밀번호가 password라는 것을 수집함

![화면 캡처 2020-11-18 181547](https://user-images.githubusercontent.com/64259087/99510864-e52d0e80-29ca-11eb-89d5-144314b4594b.png)
- 해당 명령어로 통해 들어가보면 vcn에 접속이 가능

![화면 캡처 2020-11-18 181604](https://user-images.githubusercontent.com/64259087/99510926-f7a74800-29ca-11eb-8d56-87eddaa97d07.png)
- vcn을 root 권한 즉, 관리자의 권한으로 접속이 가능해서 정보를 수집할 수 있음 (굉장한 취약점)


