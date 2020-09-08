# Blind SQL Injection
<br></br>

**1)개념**<br></br>
Blind SQL Injection은 임의의 SQL 구문을 삽입하여 인가되지 않은 데이터를 열람할 수 있는 공격 방법이라는 점에서 일반적인 SQL Injection과 동일하다.

다만 일반적인 SQL Injection의 경우에는 조작된 쿼리를 입력 해 한번에 원하는 데이터를 얻을 수 있지만, Blind SQL Injection은 쿼리 결과에 따른 서버의 참과 거짓 반응을 통해 공격을 수행한다.
<br></br>

**2)공격**<br></br><br></br>
**1.LOW 레벨**<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjQg/MDAxNTk4NTk2MDg5MTk4.uzykSdrKVtYvXWsK6-rqHDC13OWtiBA2cdsMpMGnK94g.HpHaIhS6mAogFgKTHkc6bVd7AQpZQ0nrqp_hsBCkA8cg.PNG.depeix/%EC%BA%A1%EC%B2%98.PNG?type=w773)<br></br>
User ID 필드에 숫자 1을 입력해보면 USER ID가 존자한다는 메세지가 나온다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTAx/MDAxNTk4NTk2NDEyNzM2.bVV91Rx9ZPIlrEInk2AkRLDuETkSb01FnFDCWRduBFUg.btdgYudg9dQmxC65BozVZyXJWZBTxdUgT3H0M7zxZXsg.PNG.depeix/%EC%BA%A1%EC%B2%981.PNG?type=w773)<br></br>
숫자 100을 입력할시 USER ID가 데이터베이스에 존재하지 않는다고 출력된다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjE4/MDAxNTk4NTk2NTQ4NDEz.w7re2OM3swC-J_u_6iHcz0bF842-f81SepYD0LV6mPYg.KSws8-yhgwQNOfLB4AVyw7FpYFfJkumJLiVkVxp8OkQg.PNG.depeix/%EC%BA%A1%EC%B2%982.PNG?type=w773)<br></br>
소스코드를 살펴보면 SQL 쿼리문에 대한 결과를 $result 변수에 대입하고 @MySQLi_num_rows() 함수를 이용하여 결과가 존재할 경우 row 값이 0보다 크게 되모르 '참', 반대로 1 이상이 아닐 경우 '거짓'으로 간주한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTk1/MDAxNTk4NTk2ODA5MTc4.9rAfeO8NFPOjidOvRnSwiFEK21aVLTc-lktVfzuhviwg.nqicpeZj6Ah56uo-OKFwuYvGxzeZOiZ1o-rGN0j9Xt4g.PNG.depeix/%EC%BA%A1%EC%B2%983.PNG?type=w773)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjg1/MDAxNTk4NTk2ODE3NzAx.gkBStEkoj-E3kddCZT3ittwGdQEg87NE9m13in2Kv2Yg.i0inIpWEPDsKMWCmVgfAaPeWZpuN4wIf9ryp2flAQCEg.PNG.depeix/%EC%BA%A1%EC%B2%984.PNG?type=w773)<br></br>
SQL Injection 실습에 사용했던 쿼리도 작동한다. 이 결과를 보았을때 and 구문 이후 조건이 실행되고 있음을 알 수 있으며, 이는 임의의 SQL쿼리를 실행할 수 있다는 것을 의미한다.



실습에서 사용할 함수는 substring, order by, ascii, limit이고 간단하게 설명하면

substring(컬럼 또는 문자열, 시작위치, 길이) : 문자열 자르기

ascill(strl) : strl 문자열을 아스키 값으로 반환

limit : 쿼리 결과 레코드 개수 제한

order by : 데이터베이스 데이터를 가져올 때 오름차순, 내림차순으로 정렬해주는 함수



수동으로 원하는 정보를 알아낼수 있지만 시간이 많이 걸리고 효울이 떨어지기 때문에

자동화 방식인 BurpSuite를 이용하여 Blind SQL Injection을 진행하겠다.

사용자 계정 명 확인을 예를 들어보겠다.
<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjcg/MDAxNTk4NjAyODkwODU1.m8Ow7nigh_vzQj2oiLfkgbEvpOsDZ1LC3fJAKt42LsMg.PVzpypAQlMYjkDESPribspe2scuQDHZ2tjhEbdu0HSEg.PNG.depeix/%EC%BA%A1%EC%B2%985.PNG?type=w773)<br></br>
우선 1' and ascii(substring((select user from users limit 0,1),1,1))=97# 을 DVWA 사이트에서 입력해주고

BurpSuite에 캡쳐된 패킷을 send to intruder을 클릭한 후 Positions 탭으로 이동한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTc5/MDAxNTk4NjA0NzQ2NTc3.GIg2mtuohIYZ0o2l-z25GE5S-Q4F-rSOy-PQ_iz_h3Ag.skUqT8TXembKng5VXEqMqFEaeOcrcx7RB_LTndDq6fYg.PNG.depeix/%EC%BA%A1%EC%B2%986.PNG?type=w773)<br></br>

 우선 이 내용은  users 테이블의 user 값 중 첫 글자에 아스키 코드 97(a)라는 값이 존재하는지 확인하는 내용이고 알파벳의 아스키 숫자를 자동으로 비교할 것이기 때문에 97을 지워주고 ADD $를 두 번 눌러 $$로 변경한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTUx/MDAxNTk4NjAzMzAyODk2.K0h2mfAj_578FO2bx6u6dO-oD54f-0vjc7rizfo11bAg.kKWC1DmoxMmeM7PwEWn8HFHHvX0Fzu5NsKE83Jy9zegg.PNG.depeix/%EC%BA%A1%EC%B2%987.PNG?type=w773)<br></br>

그후 Payload 탭으로 이동한다. 그리고 변수는 하나임으로 Payload set은 1로, Payload type은 Numbers로 설정한다.

효울적으로 공격하기 위해  97(a) ~ 122(z) 까지 범위를 설정한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjU4/MDAxNTk4NjA0NzU4ODMw.ymTsLvRmfxrHLRVABABobwvhqfDJDFyZ_IbOm6_UoQMg.EW5k1Ol_AZ3eunIDeg6QhveAaGUwWsLWwmQBZnqEuKMg.PNG.depeix/%EC%BA%A1%EC%B2%988.PNG?type=w773)<br></br>

공격에 성공했고 Payload 97에서 '참' 결과가 나왔다 '참'인 경우 HTTP Status 값은 200, Length는 4852로 표시됬고 '거짓'인 경우, Status는 404, Length는 4842로 표시되어 서로 값이 다른 것을 알 수 있다.



**2.Medium 레벨**<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjgw/MDAxNTk4NjA2MDg5ODI4.-N5vxRCbRaRKCAe8YqQPXmnjTboh_8l3BiGJ0SXIkAIg.dV0Xzq5C9MMa8sd_xTD6N-ZodQ2tBoTf5T53A8YukXYg.PNG.depeix/%EC%BA%A1%EC%B2%989.PNG?type=w773)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfNDkg/MDAxNTk4NjA2MzQzNDc1.f7VflbUNk1rtmLGOIFduTyOXUBkv3BA9pNT4rBzlG9Ug.G5-KrQ8tzSr5weOHj8WLlfY5IKnCLxUgdTp_JCKca_wg.PNG.depeix/%EC%BA%A1%EC%B2%9811.PNG?type=w773)<br></br>

Medium 레벨은 드롭다운 메뉴 형태로 선택하는 방식이다. BurpSuite로 패킷 캡쳐 후 Repeater를 통해 id 파라미터 값에 싱클 쿼테이션(')을 추가한 다음, GO 버튼을 눌러 Response를 확인해보면 싱글 쿼테이션(')을 필터링 처리하는 것으로 추정된다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTgx/MDAxNTk4NjA2MTgyNjk4.8JCQfwn7nnKTCxIOE9mGp_x8sqEf9h0dLhov1rNj_QEg.nbkpxV084M7Igf_1cO_oUXbWWdcgQKo7Y-2FsEkZpggg.PNG.depeix/%EC%BA%A1%EC%B2%9810.PNG?type=w773)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTU1/MDAxNTk4NjA2MzY1OTc1.ImM7pp6E0EcRKC5pYCHs21PaoE28tziZmEHS-f4d6Tgg.N22zil7R1qP2fR4ukWP2m9K-2k6uiUsapD5omDvuJa0g.PNG.depeix/%EC%BA%A1%EC%B2%9812.PNG?type=w773)<br></br>

싱글 쿼테이션(')을 빼고 입력해보면 (입력값 : 1 and 1=1) '참'임을 알 수 있다.

싱글 쿼테이션(')을 제거한 상태에서 Low 레벨과 동일하게 공격이 먹힐지 확인해보자<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTU1/MDAxNTk4NjA2MzY1OTc1.ImM7pp6E0EcRKC5pYCHs21PaoE28tziZmEHS-f4d6Tgg.N22zil7R1qP2fR4ukWP2m9K-2k6uiUsapD5omDvuJa0g.PNG.depeix/%EC%BA%A1%EC%B2%9812.PNG?type=w773)<br></br>

참 거짓을 확인하기 위해 [1 and ascii(substring((select database()),1,1))=100] 첫 글자를 d(아스키코드 100)으로 설정한 후 쿼리를 전송하면  참의 결과가 나온다<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfNDkg/MDAxNTk4NjA2MzQzNDc1.f7VflbUNk1rtmLGOIFduTyOXUBkv3BA9pNT4rBzlG9Ug.G5-KrQ8tzSr5weOHj8WLlfY5IKnCLxUgdTp_JCKca_wg.PNG.depeix/%EC%BA%A1%EC%B2%9811.PNG?type=w773)<br></br>

 "1 and ascii(substring((select database()),1,1))=50" 첫 글자에 대해 2(아스키코드 50)로 쿼리를 요청할 경우 거짓으로 반환된다.



**3.High 레벨**<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMTMy/MDAxNTk4NjExNjkyMzE1.7fu7N5yHeO8L6L5yoIFxtUWMszyhVC5lAdDWzfufpjAg.CkJr0WVGszJzFCycnus7Q__-QYBqpROYUzQsWY1avfEg.PNG.depeix/%EC%BA%A1%EC%B2%9813.PNG?type=w773)<br></br>

High 레벨은 링크클릭시 별개의 웹 브라우저 창을 이용한다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMjM2/MDAxNTk4NjEyNDA2NDEx.Z5LO7CHjL8AHhPqTIzrZx9pQ7zGkqkwJv5RnMrhM6_Ig.EU-OeosEbmay3Wn_ATBJHP_Kljgs93KyO5PxBDQfTw8g.PNG.depeix/%EC%BA%A1%EC%B2%9814.PNG?type=w773)<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfMzAg/MDAxNTk4NjEyNDI4MzI5.nl0T7u2aGHQ3BDBiW2o2EfiawDdnGugEggwBxpuEvcgg._xgQgpcCudVHZJprMGqtCVSlpxD0ptHiIyWlXHCg7c8g.PNG.depeix/%EC%BA%A1%EC%B2%9815.PNG?type=w773)<br></br>

1과 99를 입력했을시 나오는 결과이다. 참과 거짓을 판명이 되는걸 보니 Blind SQL Injection 취약점이 있다는걸 판단할 수  있다.<br></br>
![](https://postfiles.pstatic.net/MjAyMDA4MjhfODcg/MDAxNTk4NjEyNTg2MzMw.DP5cYBfIPH5b6lpP_Kd45CWleDaEnZDIdVRsIWloxRcg.V6f2ePH4gYoEdZf-SQzTqMWKo9jxZGaiTpoHOyZMEugg.PNG.depeix/%EC%BA%A1%EC%B2%9816.PNG?type=w773)<br></br>

High레벨 에서도 다양한 입력문으로 원하는 정보를 얻을수 있다 하지만 단점이라 함은 BurpSuite 자동화 공격이 안되기 때문에 하나하나 일일히 비교해야함으로 효율성이 떨어진다고 볼 수 있다.
