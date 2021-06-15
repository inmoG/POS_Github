# Blind SQL Injection
</br></br>


# 개념

`Blind SQL Injection`은 SQL Injection과 형태가 유사하지만, SQL 쿼리 요청에 대한 응답 결과가 `참, 거짓`에 따라 </br>
데이터를 획득하는 공격이다. </br>
이를 풀어 설명하면 데이터베이스 내 데이터를 `하나씩 요청`하여 이에 대한 응답으로 필드 값이나 테이블 명과 같은 정보를 찾아내는 방식이다.
</br>

- ### 특징
  - `하나의 쿼리당 하나의 응답`을 주고받기 때문에 많은 쿼리 요청이 전제되어야 하며 원하는 정보를 얻기까지 </br>소요되는 시간이 길다. 때문에 보통 자동화된 툴을 이용한다. </br>
  오류를 반환하는 SQL Injection에 비해 참과 거짓으로만 정보를 획득하므로 오류가 발생하지 않은 사이트에서도</br> 공격이 가능하다. 

- ### 공격 유형
  - ### Boolean 기반
    - 요청 쿼리에 대한 응답이 참, 거짓에 따라 `반복적`으로 수행하여 추측하는 `점진적인` 공격 방식. </br>앞서 언급했던 것과 같다.
  - ### Time 기반
    - 쿼리에 대한 응답이 `참`일 경우 `sleep()` 함수를 사용하여 특정 시간만큼 지연시키는 공격 방식이다. </br>거짓일 경우 `sleep()` 함수가 실행되지 않으므로 시간 지연 없이 응답이 이루어진다.
</br></br></br></br>

# 공격

</br></br>


# Low 레벨

공격을 진행하기에 앞서 Low 레벨의 소스코드를 살펴보자. 

![](https://images.velog.io/images/kmk9502/post/d4be97de-8c74-4b24-84b1-4bbbe5ace467/Low%20%EB%A0%88%EB%B2%A8%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

위 소스코드에서 SQL 쿼리문에 대한 결과를 ` $result` 변수에 대입하고, 이를 `@MySQLi_num_rows()` 함수를 이용하여 결과가 존재할 경우, 즉 $num의 값이 1 이상이 되면  `if-else` 조건문에 따라 데이터베이스 내에 입력 값이 존재한다는 문자열을 출력하고, </br> 결과가 존재하지 않는 경우, $num의 값이 0이 되면서 입력 값이 존재하지 않는다는 문자열을 출력한다.</br></br>

따라서 ` $num > 0`일 경우 `참`이고, ` $num == 0`일 경우 거짓으로 간주한다.
</br></br>

이제 SQL Injection 공격과 비슷하게 임의의 SQL 쿼리를 실행할 수 있는지 확인한다.

![](https://images.velog.io/images/kmk9502/post/a3f42bf9-0ac8-4985-b151-210c3124c724/SQL%20Injection%EC%97%90%EC%84%9C%20%EB%8F%99%EC%9D%BC%ED%95%9C%20%EC%9E%85%EB%A0%A5%EA%B0%92%EC%97%90%20%EB%8C%80%ED%95%9C%20%EB%8B%A4%EB%A5%B8%20%EA%B2%B0%EA%B3%BC.png)

![](https://images.velog.io/images/kmk9502/post/bdecb030-0221-40a1-ac7c-3d91979201df/and%20%EA%B5%AC%EB%AC%B8%20%EC%9D%B4%ED%9B%84%20%EC%A1%B0%EA%B1%B4%20%EC%8B%A4%ED%96%89_%EC%9E%84%EC%9D%98%EC%9D%98%20SQL%20%EC%BF%BC%EB%A6%AC%20%EC%8B%A4%ED%96%89%20%EA%B0%80%EB%8A%A5.png)

결과를 보니 or와 and `구문 이후 조건이 실행`되고 있음을 알 수 있다. 즉, 임의의 SQL 쿼리를 실행할 수 있다.
</br></br>


본격적으로 공격을 진행하기 전에 Blind SQL에서 많이 사용하는 함수 중 실습에 사용할 함수는 `substring, order by, ascii, limit`이다. 실제 공격과정에서는 더 다양한 함수를 사용한다.</br></br>

|함수|설명|공격 예시|결과|
|:--|:---:|:----:|:--:|
|substring(컬럼 또는 문자열, 시작 위치, 길이)|문자열 자르기|SELECT substring("kimminQ", 2, 4)|immi|
|ascii(str1)|str1 문자열을 아스키 값으로 반환|ascii(a)|97|
|limit</br>|쿼리 결과 레코드 개수 제한|SELECT * FROM [TABLE NAME] LIMIT 5;</br></br>SELECT * FROM [TABLE NAME] LIMIT 4, 10;|레코드 5개 가져오기</br></br>레코드 5번째부터 10개 추출|
|order by|데이터베이스에서 데이터를 가져올 때 오름차순, 내림차순으로 정렬해주는 함수|
||

</br>
SQL 쿼리 실행이 가능한 것을 확인 했으니 호스트명을 참과 거짓 값을 기반으로 추측해보자. </br>
현재 호스트명은 도커 컨테이너 ID로 설정되어 있다는 것을 알고 있으니 ID의 첫글자인 d를 전송한 결과를 살펴보자.

![](https://images.velog.io/images/kmk9502/post/52329408-8aa9-4c03-a9c4-da6411c42174/%ED%98%B8%EC%8A%A4%ED%8A%B8%EB%AA%85%20%ED%99%95%EC%9D%B8_%ED%98%84%EC%9E%AC%20%EB%8F%84%EC%BB%A4%20%EC%BB%A8%ED%85%8C%EC%9D%B4%EB%84%88%20ID.png)

`@hostname` 내에 존재하는 호스트명인 `dc217aed2f03` 중 첫번째인 d를 `substring()` 함수로 가져온 결과이다. </br>
`입력값 : 1' and substring((select @@hostname),1,1) = 'd'#` </br></br>

호스트명의 한 글자씩 위의 입력값과 같이 전송한 결과를 모두 모으면 하나의 호스트명을 얻을 수 있다. </br></br>
물론, 호스트명 뿐만 아니라  데이터베이스 명, 테이블 명, 사용자 계정 확인, 사용자 계정 패스워드 확인 등의 정보를 위와 같이 얻을 수 있지만, 그 과정이 너무 오래 걸리고, 값을 알지 못하는 상황에서는 수많은 경우의 수를 전부 대입해야 한다. </br></br>

이러한 효율성의 문제를 해결하기 위해 `자동화된 도구`인 `BurpSuite 내의 Blind SQL Injection 기능`을 사용한다. 
</br></br>

해당 도구를 사용하여 사용자 계정 명을 확인한다. 현재 사용자 계정 명은 admin 이며, 아스키 코드 값은 다음과 같다.

|문자|a|d|m|i|n|
|:--:|:--:|:--:|:--:|:--:|:--:|
|시작 위치| 1 | 2 | 3 | 4 | 5 |
|10진수| 97 | 100 | 109 | 108 | 110 |
|16진수| 0x61 | 0x64 | 0x6D | 0x69 | 0x6E |
| |
</br></br>

## Blind SQL Injection 공격 진행 과정
</br>

1. 입력 값으로 `1' and ascii(substring((select user from users limit 0,1),1,1))=97#` 을 입력한다. </br> 이 명령어는 users 테이블의 user 값 중 첫 글자에 아스키 코드 97(a)라는 값이 존재하는지 확인하는 명령어이다.</br></br>
2. 프록시 기능을 수행하는 BurpSute를 이용하여 패킷을 잡아두고 상단 메뉴에 있는 `Intruder`로 패킷을 보낸다.</br></br>
   ![](https://images.velog.io/images/kmk9502/post/d6ff5f94-72cd-42e3-b843-9fa12ada01f0/%EC%9E%90%EB%8F%99%ED%99%94%20%EA%B3%B5%EA%B2%A9%EC%9D%84%20%EC%9C%84%ED%95%B4%20%EC%88%98%EC%A0%95%ED%95%A0%20%EC%9A%94%EC%B2%AD%20%EA%B0%92.png)</br></br>
3. Intruder의 `Position` 창에서 자동화 공격을 진행할 부분을 `ADD $` 버튼을 두 번 눌러 `$$`로 변경한다. </br> $ $의 사이에 자동화 공격을 위한 아스키 코드가 들어가게 된다.</br></br>
   ![](https://images.velog.io/images/kmk9502/post/7777318d-0f51-4da5-8748-04d2ab84216e/Add%EB%A1%9C%20%EC%9E%90%EB%8F%99%ED%99%94%20%EA%B3%B5%EA%B2%A9%EC%9D%84%20%EC%A7%84%ED%96%89%ED%95%A0%20%EB%B6%80%EB%B6%84.png)</br></br>
4. `Payload ` 창에서 payload 설정을 진행한다. payload options의 시작 숫자를 97(a)로 설정한 이유는 공격 범위를 한정시켜 </br>공격의 효율성을 증가시키기 위함이다. </br>물론, 실제 공격 대상의 정보가 없을 경우에는 `Brute Force` 공격과 유사하게 범위를 설정해야 한다.</br></br>
   ![](https://images.velog.io/images/kmk9502/post/939c3ab4-713f-4266-9064-866cd4b983d0/Payload%20%EC%84%A4%EC%A0%95.png)</br></br>
5. 설정이 완료된 후 `start attack` 버튼을 누르면 공격이 진행된다. 결과 창에서</br> `HTTP status 값이 200, Length는 5654`로 표시되는 것은 `참`이며, </br>`HTTP status 값이 404, Length는 5667`로 표시되는 것은 `거짓`으로 판별할 수 있다. </br></br>
   ![](https://images.velog.io/images/kmk9502/post/d6e00f51-db87-477c-a1a2-cb302f7670e2/%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)
   
    ![](https://images.velog.io/images/kmk9502/post/efdf204d-d6cd-438d-a932-8e90fced1251/%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B52.png)</br></br>

</br></br></br>


# Medium 레벨

Medium 레벨은 SQL Injection Medium 레벨과 동일하게 드롭박스 메뉴 형태로 선택하는 방식이다. </br>
</br>
BurpSuite에서 패킷 캡처 후 Repeater를 통해 `id 파라미터 값`에 싱클 쿼테이션( ' )을 추가한 다음 응답 결과를 확인해보자.</br>

![](https://images.velog.io/images/kmk9502/post/3aa227e4-32d9-407b-aea2-4f9ca53517d5/%EC%8B%B1%EA%B8%80%20%EC%BF%BC%ED%84%B0%20%EC%82%BD%EC%9E%85%20%ED%9B%84%20%EC%8B%A4%ED%96%89%20%EA%B2%B0%EA%B3%BC.png)

![](https://images.velog.io/images/kmk9502/post/3ab8e74c-2d21-425d-bfae-352a0dd921fb/%EC%8B%B1%EA%B8%80%20%EC%BF%BC%ED%84%B0%20%EC%82%BD%EC%9E%85%20%ED%9B%84%20%EC%8B%A4%ED%96%89%20%EA%B2%B0%EA%B3%BC2.png)

Low 레벨과는 다르게 거짓 값이 출력되는 것을 확인할 수 있다. 이 결과를 통해 `싱글 쿼터( ' )를 필터링` 한다는 것을 유추할 수 있다. </br></br>

입력된 모든 값에 대해 필터링을 하는 것이 아닌, 단지 싱글 쿼터에 대한 필터링을 적용한다는 가정 하에 싱글 쿼터를 제거하여 Blind SQL Injection을 진행해 보자.

![](https://images.velog.io/images/kmk9502/post/659d0322-858a-4b03-a454-1550677264e9/%EC%8B%B1%EA%B8%80%20%EC%BF%BC%ED%84%B0%20%EC%A0%9C%EA%B1%B0%20%ED%9B%84%20%EC%8B%A4%ED%96%89%20%EA%B2%B0%EA%B3%BC.png)

![](https://images.velog.io/images/kmk9502/post/bbe886e2-f654-4741-b859-53256929bbe9/%EC%8B%B1%EA%B8%80%20%EC%BF%BC%ED%84%B0%20%EC%A0%9C%EA%B1%B0%20%ED%9B%84%20%EC%8B%A4%ED%96%89%20%EA%B2%B0%EA%B3%BC2.png)

싱글 쿼터를 제거하여 `1 and 1=1`을 삽입하여 전송하자 `참` 값을 응답하는 것을 확인할 수 있다.</br>
즉, Medium 레벨에서는 단지 싱글 쿼터에 대한 필터링만을 적용하고 있다.</br></br>

Medium 레벨에서의 취약점을 이용해 데이터베이스의 이름을 확인해 보자. </br>
`입력 값 : 1 and ascii(substring((select database()),1,1))=100`</br>
`해석 : 데이터베이스의 이름 중 첫 글자에 아스키 코드 100(d)이 존재하는지 확인하는 명령어`

![](https://images.velog.io/images/kmk9502/post/d1d4aaf5-3dfb-47f8-a1a0-67e72f4cf7a8/%EC%8B%B1%EA%B8%80%20%EC%BF%BC%ED%84%B0%20%EC%A0%9C%EA%B1%B0%20%ED%9B%84%20%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%B2%A0%EC%9D%B4%EC%8A%A4%EB%AA%85%20%EC%B2%AB%20%EA%B8%80%EC%9E%90%20%ED%99%95%EC%9D%B8.png)

![](https://images.velog.io/images/kmk9502/post/f2e42052-8b67-4e99-8765-a849a2b7147c/%EC%95%84%EC%8A%A4%ED%82%A4%EC%BD%94%EB%93%9C%20100%EC%9D%B4%20%EC%B2%AB%20%EA%B8%80%EC%9E%90%EC%9D%B8%20%EA%B2%83%EC%9D%84%20%ED%99%95%EC%9D%B8.png)

명령어 입력 결과, `참` 값이 출력되는 것을 확인할 수 있다. 즉, 데이터베이스의 첫 글자는 d가 맞다.

</br></br></br>


# High 레벨

High 레벨에서는 SQL Injection High 레벨과 동일하게 별도의 페이지에서 값을 입력하도록 되어있다. </br>
</br>

High 레벨에서도 참과 거짓을 구분할 수 있는 Blind SQL Injection 취약점이 있는지 확인해보자. </br>

![](https://images.velog.io/images/kmk9502/post/5bf210a0-df9a-4a9b-9251-ff4d5431bea8/%EC%B0%B8%20%EA%B1%B0%EC%A7%93%20%EA%B5%AC%EB%B6%84%20%EC%B7%A8%EC%95%BD%EC%A0%90%20%ED%99%95%EC%9D%B8%201.png)

![](https://images.velog.io/images/kmk9502/post/131c8f5b-a67f-4b58-b39e-fe866343bc51/%EC%B0%B8%20%EA%B1%B0%EC%A7%93%20%EA%B5%AC%EB%B6%84%20%EC%B7%A8%EC%95%BD%EC%A0%90%20%ED%99%95%EC%9D%B8%202.png)

결과를 보니 숫자 1을 입력하면 데이터베이스 쿼리 결과가 `참`임을 알 수 있다. </br>
반대로, 숫자 99를 입력하면 쿼리 결과는 `거짓`, 즉 데이터베이스 내에 존재하지 않는다는 메시지를 출력한다.</br>
즉, 참과 거짓을 구분하고 그 결과를 출력하는 취약점을 확인할 수 있다.
</br></br>

-   ## 자동화 공격 불가
    </br>

    High 레벨에서는 위 사진과 같이 `입력값을 전송하는 페이지와 출력되는 페이지가 나뉘어져 있고`, `한번 사용한 패킷은 재사용할 수 없기` 때문에 기존 패킷에서 원하는 값만 바꾸어 반복적으로 패킷을 전송하는 자동화 도구는 High 레벨에서는 오류가 발생하게 된다.
</br></br>

따라서 High 레벨의 경우 `수동`으로 공격을 진행하애 한다. </br>
`입력값 : 1' and substring((select @@datadir),1,1)='/' #`
</br>

![](https://images.velog.io/images/kmk9502/post/5cd25740-06a9-429c-97fa-c0af36954de6/datadir%20%EC%B2%AB%20%EB%B2%88%EC%A7%B8%20%EB%AC%B8%EC%9E%90%20%EB%B9%84%EA%B5%90%20%EA%B2%B0%EA%B3%BC.png)

다행히 High 레벨에서는 자동화 공격만을 막아놓았을 뿐, 싱글 쿼터( ' ) 등의 입력값은 필터링하지 않는다.</br>위 결과는 데이터베이스 서버의 `디렉토리`를 확인한다. </br>
`@@datadir` 함수의 결과는 데이터베이스의 디렉토리 경로이기 때문에 첫 글자가 `/`인 것을 확인할 수 있다.
</br></br>

두 번째 값과 세 번째 값, 그리고 네 번째 값은 아래와 같다. 

![](https://images.velog.io/images/kmk9502/post/3b757ba8-fd19-47b1-8ebf-28ac6360f209/%EC%88%98%EB%8F%99%EC%9C%BC%EB%A1%9C%20%EC%B0%B8%20%EA%B1%B0%EC%A7%93%20%ED%99%95%EC%9D%B8.png)

![](https://images.velog.io/images/kmk9502/post/2a3bf4a0-e7e4-4074-9b0e-87dbcfd423cb/%EC%88%98%EB%8F%99%EC%9C%BC%EB%A1%9C%20%EC%B0%B8%20%EA%B1%B0%EC%A7%93%20%ED%99%95%EC%9D%B82.png)

![](https://images.velog.io/images/kmk9502/post/b9cd777e-cfe7-4def-909b-a8475ada478c/%EC%88%98%EB%8F%99%EC%9C%BC%EB%A1%9C%20%EC%B0%B8%20%EA%B1%B0%EC%A7%93%20%ED%99%95%EC%9D%B83.png)

위 과정을 거쳐 `@@datadir`의 첫 번째 경로는 `/var`이라는 것을 알 수 있었다. </br>
그러나, @@datadir의 경로 정보는 /var 뒤에 더 존재할 것이다. 
</br>High 레벨에서는 자동화 도구가 작동하지 않기 때문에 문자를 하나하나씩 확인하다보면 최종결과를 얻을 수 있지만, </br>매우 비효율적이다.