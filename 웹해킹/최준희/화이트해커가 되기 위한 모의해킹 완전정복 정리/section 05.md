# Section 05
## 21강
- 모의 해킹의 첫번째 단계 정보수집
    - 패시브 스캐닝 = 정찰
    - 액티브 스캐닝
- 이미 공개 되어 있는 정보를 이용하여 정보를 수집
    - 검색 사이트
    - WHOIS, NETCRAFT 등
- 해커의 활동이 드러나지 않음
## 22강
- 구글 해킹 기법
    - site:(사이트 주소) : 검색 기관을 특정사이트로 제한할 수 있음
    - site:(사이트 주소) -site(문자열) : 검색 기관을 특정사이트로 제한하고 입력한 문자열은 검색되지 않음
    - site:(사이트 주소) filetype:(특정파일명) : 특정 주요의 파일만 찾을 수 있음
    - inurl:admin : admin(관리자) 페이지가 어디에 존재하는지 검색 가능
    - intitle:() : 웹 페이지의 타이틀 검색
## 23강
- netcraft : 주소 searchdns.netcraft.com
- KISA (한국인터넷진흥원) : 주소 whois.kisa.or.kr
## 24강
- theharvester -d bloter -b (google) : 이메일 수집
## 25강
- recon-ng : 파이썬으로 개발된 정찰용 프레임 워크 -> 다양한 모듈들을 독립적으로 사용 가능
    - help : 사용가능한 명령어
    - search whois_pocs : 모듈 검색
    - use () : 모듈 사용
    - show info : 모듈 설명
    - help (show) : show 뒤에 어떤 명령어가 있어야 하는지 알려줌
    - show options : 모듈이 실행하기 위해서 필요한 옵션 표시
        - required 는 무조건 설정해야함
    - set source (microsoft.com) : 도메인을 microsoft로 source를 설정함
    - run : 모듈을 실행
    - show contacts : 수집한 이메일과 정보 출력
    - search bing_domain_web : 서브 도메인을 알아낼때 사용
## 26강
- **Shodan** : 주소 www.shodan.io
    - 인터넷으로 연결되어 있는 사물인터넷을 검색하는 사이트
- city	입력한 도시에서의 검색 결과	             
- country	입력한 나라에서의 검색 결과	         
- geo	입력한 위도/경도 좌표 근처의 검색 결과	  
- hostname	입력한 호스트 네임이 포함되는 결과	  
- net	입력한 클래스에 맞는 검색 결과	          
- os	입력한 os를 포함하는 정보	             
- port	입력한 포트와 일치하는 검색결과           
- before/after	입력한 날짜 전/후의 검색 결과	
- title	HTML 의 title과 일치하는 정보 검색	
- html	HTML의 모든 소스 코드 중에서 해당 단어를 포함한 것을 검색	
- product	소프트웨어나 제품의 이름을 기준으로 검색	
- org	해당 기관을 포함한 검색 결과	
- asn	Asn(autonomous system number)을 기준으로 검색	
- category	카테고리 기준으로 검색. 사용가능한 카테고리는 ics와 malware	
- has_ipv6	검색 결과에 ipv6의 포함 여부를 true, false로 결정	
- has_screenshot	검색 결과에 screenshot포함여부를 true, false로 결정	
- ip	넷필터명을 기준으로 검색	 
- isp	IPS를 기준으로 검색	 
- postal	우편번호를 기준으로 검색(미국에만 해당)	 
- region	주 이름을 기준으로 검색	 
- version	제품 버전을 기준으로 검색	
- vuln	취약점 CVE ID를 기준으로 검색	 
    