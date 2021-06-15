# Weak Sessiom IDs
<br></br>
**개념** : 웹 애플리케이션 구현에 있어서 서비스에 접근하는 사용자의 인증 값이나 세션, 쿠키 생성/관리 구현에서 발생하는 취약점을 공격하는 기법이다. 이러한 취약점을 이용하여 비인가자가 로그인 없이 서비스 페이지에 접근하거나 관리자 페이지까지 접근할 수 있다. 또한, 다른 사용자의 인증 값을 가로채서 다른 사용자인 것처럼 가장할 수 있다.


**세션** : 통신에서는 사용자와 컴퓨터, 또는 두 대의 컴퓨터 간의 활성화된 접속을 의미하며, 프로그램 사용과 관련해서는 한 응용프로그램의 기동을 시작해서 종료할 때까지의 시간


**세션의 동작원리**

1. 클라이언트(웹 브라우저)에서 페이지 요청
2. 웹 서버에서는 HTTP Request 정보 내 세션 ID를 확인
3. 세션 ID가 없을 경우 세션 ID 값을 생성 후 클라이언트에 HTTP Response로 전송
4. 클라이언트는 세션 ID를 쿠키에 저장
5. 클라이언트가 HTTP Request 내 세션 ID를 포함하여 전송
6. 웹 서버는 세션 ID를 기반으로 이전 상태 정보를 확인



**쿠키** : 웹사이트에 접속할 때 자동적으로 만들어지는 임시 파일로 이용자가 본 내용, 상품 구매 내역, 신용카드 번호, 아이디(ID), 비밀번호, IP 주소 등의 정보를 담고 있는 일종의 정보 파일



**쿠키의 동작원리** 

1. 클라이언트(웹 브라우저)에서 페이지 요청
2. 웹 서버에서 요청된 페이지에 대해 HTTP 헤더에 쿠키를 포함하여 응답
3. 응답된 쿠키 정보를 클라이언트 측에서 저장, 관리
4. 클라이언트에서 재요청 시 쿠키를 함께 전송
5. 웹 서버는 쿠키 정보를 읽어들인 후 이전 상태 정보를 확인


**세션과 쿠키의 비교**<br></br>

| 구분 | 세션 | 쿠키 |
|:----------:|:----------:|:----------:|
| 저장 위치 | 서버 | 클라이언트 |
| 저장 방식 | 객체 형 | 텍스트 형식 |
| 자원 사용 | 서버 리소스 사용 | 클라이언트 리소스 사용 |
| 용량 제한 | 서버 설정에 따라 다름 | 한 도메인당 20개 총 300개 저장 |
| 용도 | 서버 이용 시 사용자 정보 유지 | 사이트 재방문 시 사용자 정보 기억 |

<br></br>

# **공격**

**# 1. Low 레벨**
<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjg0/MDAxNTk4NjgwNjA4NDMw.xeqAL-MJ6FW9mOYmtIg9oO5HXxlPNZgZzXFb14-fqesg.WG5_NylgmX-UT0XjUw_eDHKIxr_D20bJTqrFOMZ3lpQg.PNG.depeix/image.png?type=w966)<br></br>
BurpSuite를 실행하고 Generate 버튼을 누른다. 패킷이 캡쳐된 것을 확인해 보면<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjUz/MDAxNTk4NjgwNzU5NzEx.BVyOq-RhyOre-7fQ1lQ0DS4rzuT1YYVZ9ax7fHuMf8Eg.DOGTdJNNDz9Zy2udixUooWI4yevqFHqcoSe69JnytPsg.PNG.depeix/%EC%BA%A1%EC%B2%98.PNG?type=w966)<br></br>
dvwaSession 값이 1인 걸 확인할 수 있다. 다시 한번 Generate 버튼을 누르면<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjYx/MDAxNTk4NjgwODI2ODIz.TyMwwbpLKU4hdrCb4F3Ckvc006ds1sX2QMf5Y2ZYW9Ig.2BhDmV6kLVOXrj7-o_kDO5mSVxgEwMsuRTch1LM4Z9Eg.PNG.depeix/%EC%BA%A1%EC%B2%981.PNG?type=w966)<br></br>
dvwaSession 값이 2로 1이 증가된 걸 확인할 수 있고 즉 Generate 버튼을 누를 때마다 값이 1이 증가되는 걸 알 수  있다<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjA4/MDAxNTk4NjgwOTM1MjU1.WXud-WktqHwjmyoh6EdtNngL84UnVWcDgqY1muqU1vkg.QrNvE4Uq5XOWYXSgaR1G8gul8T_XAXyiNTeBbI20GRIg.PNG.depeix/image.png?type=w966)<br></br>
소스코드를 보면 최초 세션 값이 설정되지 않았을 경우, 0으로 지정한 후에 1씩 추가하여 쿠키 값에 추가된다.<br></br><br></br>
**# 2.Medium 레벨**<br></br>
Low 레벨과 동일하게 Generate를 눌러 패킷을 캡쳐한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMTc2/MDAxNTk4NjgxMTE3NDY2.KEgGchV17QCeySVL-Z9EYT7EUGGCwCP1ZK7g1NZicG8g.JfsoE_oE42nIHMFdomhcqYOEflp7w7n68PEyJn-1p7Yg.PNG.depeix/%EC%BA%A1%EC%B2%982.PNG?type=w966)<br></br>
이전에 가지고 있던 쿠키 값을 바탕으로 서버 측에 전송하기 때문에 dvwaSession 값이 3이 된 걸 볼 수 있고 이건 Medium 레벨에서의 php를 통해 해석하기 때문에 발생하는 문제로써, HTTP history 탭에서  패킷을 확인해보면 제대로 된 dvwaSession 값을 확인할 수 있다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMTM3/MDAxNTk4NjgxNzY2NDI5._QDa21rd_BCvWm4PQvHrNpfjatALjh7CMnmeHYzw7SQg.o31RZoOyi7G3_DNc5cXBOBsR6_BwpzisTaGx4gcwyIQg.PNG.depeix/%EC%BA%A1%EC%B2%983.PNG?type=w966)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfOTUg/MDAxNTk4NjgxODI1Nzc2.SXQ5m6nCcsMmjmHgwmd5yk-nAxwfF9udRS2dpH_HEHsg.bGfGiFna15vxAAyGkuB_IyoYk0H-zoQi5swPN3RzGqEg.PNG.depeix/%EC%BA%A1%EC%B2%984.PNG?type=w966)<br></br>
세션 쿠키의 값이 1598681705이고 다시 Generate 버튼을 누를 시 1598681799로 증가된 크기가 Low 레벨과 다르다는 걸 알 수 있다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMTQ3/MDAxNTk4NjgxOTA4NzU2.7Wzye9ONlWEZNek8ry4y18phE2uoyrL0-4NR31J4Bp8g.9zECHOxBPh61Lskm3sXWFy6hAWnH596Om9URmOEjOBMg.PNG.depeix/image.png?type=w966)<br></br>
임의의 숫자가 증가하는 것으로 보이는데 소스코드를 한번 확인해 보면  쿠키 값으로 time() 함수를 사용한다 time() 함수는 현재의 유닉스 타임스탬프 값을 변환해 주는 함수로서 1970년 1월 1일 0시 0분 0초로부터 지나온 초를 계산하여 정수 형태로 반환하는 기능을 한다. unix timestamp 값을 변환해 주는 웹 사이트를 활용하여 각각 1598681705, 1598681799을 반환해보자<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjcg/MDAxNTk4NjgyMTMzMTcx.q6Wf2dHkyMVEDn45zogZj5z5XqVKqbMVpcsC-eGfReog.8EqIrUBNGlyrd_Oe9oaeQNW9lahbinotVi7epTdHIrYg.PNG.depeix/image.png?type=w966)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjYz/MDAxNTk4NjgyMTE5MTgw.ghpxgsIKcCXdhsBJco-agXyuXID7iImS9u6Od15zgYMg.T29clrRg_NIkE5gnnaXFk02omtTeucALs-4ehfdufvIg.PNG.depeix/image.png?type=w966)<br></br>
각각 Genertae 버튼을 클릭한 시점의 타임스탬프를 설정했다는 걸 알 수 있고 그러므로 임의 조작이 쉽지 않다는 것도 알게 되었다.<br></br><br></br>
**# 3.High 레벨**<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjU0/MDAxNTk4Njk3Mzc4NTY1.N-QqytYFQm_guEWHHqiGAhSiC6cq2AZwL3lVm6vlAAcg.7BmnTVBo7BQUCmXwIGEvmH0K1WRZPnu-RNf8oszJDbsg.PNG.depeix/image.png?type=w966)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjc4/MDAxNTk4Njk3NDA4MjAy.Ja6aAt2Sq7uvU7k6H6Xi1B0mQKqYQmM_0_SYd314aOEg.vdCvbEUjAdBjx4kS3Gdv37AbauQPD_C-H723H_C2YbQg.PNG.depeix/image.png?type=w966)<br></br>
이전 실습과 동일하게 Generate 버튼을 눌러 BurpSuite로 패킷 캡쳐를한다.
하지만 캡쳐된 패킷을 보면 Medium에 사용된 unix timestamp이 세션에 할당된 것을 볼 수 있다. 이것은 Medium에서의 쿠키 데이터 때문에 일어난 현상으로 High 레벨에서의 세션 값이 제대로 나오지 않기 때문에 Response에 있는 dvwaSession 값을 확인해보면 우선 연속으로 2번 패킷을 캡쳐하여 2개의 값을 얻었다(c4ca4238a0b923820dcc509a6f75849b, c81e728d9d4c2f636f067f89 cc14862c)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjQy/MDAxNTk4Njk3NDc0MzQ2.Ig3brN3vIHUE6L97RTmY0cTAwHBzGnKYC3sGw41spiIg.8tM8-dViTAmQ0E4N0Ejqdh86Fc6Qn_5OK0CMqnVmd0cg.PNG.depeix/image.png?type=w966)<br></br>
소스코드를 확인해보면 세션 값이 md5로 암호화되는 걸 알 수 있다. 세션 값을 복호화 해보면<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfMjk2/MDAxNTk4Njk3NjY4ODM0.9OYgWpC2P1R8643ODlHsYfZee8PBNEH0xf1XzfVqqZUg.tmonV3Z4tAIz0MvXuFyqRwiHnYexEsbW7k_lwNai3Ckg.PNG.depeix/image.png?type=w966)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjlfNjUg/MDAxNTk4Njk3NzIyMjM0.JuOtdqvRPPfLhmqzFoqqUkyRAVUyyUKKR3qVoJzZoIMg.4Nq26E0GGMJd1eWLGFNc6E9-pZVXs1H_uSCP48vIRsQg.PNG.depeix/image.png?type=w966)<br></br>

복호화 한 세션 값이 각각 1, 2로 나오는 걸 봐선 세션 값은 1씩 증가하고 있고 md5로 암호화돼있다는 걸 알 수 있다.
