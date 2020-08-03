# 개념
소스 코드 안에 웹 서버 내 혹은 원격의 다른 파일을 삽입하여 공격자가 원하는 코드를 실행하는 공격이다.</br>
File Inclusion 취약점은 공격자가 지정한 URL 내 php파일을 적절한 검증 혹은 필터링 없이 읽어들여 사용할 때 발생한다. </br>
이는 주로 PHP 애플리케이션의 include()와 require() 설정의 취약점에 기인하며, 서버 내 파일의 내용이 유출되거나 공격자가 작성한 코드를 서버가 실행하는 등의 피해를 입을 수 있다. </br>File Inclusion 취약점은 삽입하는 파일의 위치에 따라 `Local File Inclusion (LFI)` 과 `Remote File Inclusion (RFI)`으로 나눌 수 있다.

-  ### `Local File Inclusion`
    웹 브라우저를 통해 서버 내 파일에 접근하는 공격 방식. </br>
    클라이언트가 요청한 파일을 PHP의 include()를 활용하여 서버 내 파일 내용 노출 및 실행이 가능하다.</br> 
- ### `Remote File Inclusion`
    Local File Inclusion과 유사한 방법으로 서버 내 파일이 아닌 원격(외부 서버)의 파일을 가져와 실행하는 공격 방식.</br></br></br></br></br>




# Low 레벨

# 취약점 분석

실습 페이지 접속 시 URL 창에 보이는 파라미터인 `?page=include.php` 값을 주목하자. </br>
이 파라미터 값을 활용하여 공격을 진행할 수 있다.

![](https://images.velog.io/images/kmk9502/post/1a080e27-c25a-4031-9099-bdbaeecc577d/%EC%B5%9C%EC%B4%88%20File%20Inclusion%20%EC%8B%A4%EC%8A%B5%20%ED%8E%98%EC%9D%B4%EC%A7%80%20%EC%A0%91%EC%86%8D%20%EC%8B%9C%20%ED%99%94%EB%A9%B4.png)

file.php 링크를 클릭하면 `?page` 파라미터가 `file1.php`로 변경되었다.</br>
이는 페이지를 호출할 때 다른 파일을 Include하여 실행한다는 증거이다.</br>
해당 취약점을 이용하여 Local File Inclusion 공격을 진행하자.</br>

![](https://images.velog.io/images/kmk9502/post/63b909be-156e-4ecb-8fbc-e1ca63d0b5e9/file1_php%20%ED%81%B4%EB%A6%AD%20%EC%8B%9C%20%EC%A3%BC%EC%86%8C%20%ED%99%95%EC%9D%B8.png)

# 공격

해당 페이지의 사용자 정보를 빼내오기 위해 주소창의 `page` 파라미터의 file.php를 `/etc/passwd`로 수정하여 중요 정보를 포함한 페이지를 호출한다.
호출 결과, 웹 브라우저 상단에서 해당 내용을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/60efb836-2c9e-43c4-bd8b-6e8141235ff2/page%20%ED%8C%8C%EB%9D%BC%EB%AF%B8%ED%84%B0%20%EC%A1%B0%EC%9E%91%20%ED%9B%84%20etc_passwd%20%EB%82%B4%EC%9A%A9%20%ED%99%95%EC%9D%B8.png)

다음은 웹 서버 내의 특정 위치에 파일을 생성하고 해당 파일을 실행시켜보자.</br>
웹 서버에 `Command Injection` 공격을 활용하여 악성 `php` 파일을 생성해보자. 

![](https://images.velog.io/images/kmk9502/post/63495dce-1fdc-4ce9-9535-5db288712ee4/%EC%8B%A4%ED%8C%A8_%EB%AA%85%EB%A0%B9%EC%96%B4%20%EC%82%BD%EC%9E%85%EC%9D%84%20%ED%86%B5%ED%95%9C%20php%20%ED%8C%8C%EC%9D%BC%20%EC%83%9D%EC%84%B1.png)

위 명령어로 hack.php 파일이 서버 내 /tmp 경로에 생성되었다. </br>
다음은 생성한 hack.php 파일을 호출하는 `Local File Inclusion` 공격을 진행하기 위해 주소창을 이용해 `상위 디렉토리`에 접근하여 hack.php 파일을 호출한다.

![](https://images.velog.io/images/kmk9502/post/22cd1f1b-1163-4f66-9b76-762c56ca0b53/%EC%8B%A4%ED%8C%A8_tmp_hack_php%20%ED%8C%8C%EC%9D%BC%20%ED%98%B8%EC%B6%9C.png)

서버 내에 생성한 hack.php 파일은 실행 시 해당 서버 내에서 백그라운드로 5555 포트를 여는 기능을 한다. </br>
위 사진처럼 주소창으로 파일 실행 시 웹 브라우저 상에 아무런 변화가 없다. </br>그러나 공격자 측에서 터미널에 `netcat`을 통해 5555 포트로 접속을 시도하고 `netstat`를 통해 5555 포트에 접속한 것을 확인할 수 있다.
</br></br></br></br></br>

# Medium 레벨

# 취약점 분석

Low 단계에서 `page` 파라미터에 `/etc/passwd` 파일을 입력하여 내용을 출력하는 공격은 Medium 단계에서도 유효하다. 그러나 Local File Inclusion 공격이나 `http://` 혹은 `https://`를 사용해서 원격의 파일을 실행하는 Remote File Inclusion 공격은 파일을 찾을 수 없다는 오류가 발생한다.</br></br>
해당 페이지의 소스코드를 분석하여 원인을 알아보자. </br>
str_replace() 함수를 통해 `"http://", "https://", "../", "..\"`에 해당하는 문자열을 필터링하는 구문을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/e11c86df-e082-42a3-9b75-2baa43044b57/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7(236).png)

그러나 이처럼 특정 문자열을 `' '(빈문자)`로 없애는 경우에 한해서 필터링되는 문자열을 중간에 한번 더 넣어주어 필터링을 우회할 수 있다. </br>
칼리 리눅스의 아파치 서버에 생성한 `php 파일`을 호출하도록 한다.

![](https://images.velog.io/images/kmk9502/post/9f248f61-dc2f-4c73-820a-1e6299fb30e8/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7(239).png)

php 파일 내용대로 DVWA 서버에 `5555 포트`가 열린 것을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/8879b644-7ec0-472f-bbbe-0e8e045cfe7f/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7(238).png)
</br></br></br></br></br>

# High 레벨

# 취약점 분석

Low, Medium 레벨에서 통했던 `page` 파라미터 값 조작을 통한 명령 실행이 High 레벨어서는 통하지 않는다. 

![](https://images.velog.io/images/kmk9502/post/7bde9622-2bd5-432c-ab01-55d07d1e6f66/High%EB%A0%88%EB%B2%A8_%ED%8C%8C%EC%9D%BC%20%ED%98%B8%EC%B6%9C%20%EC%8B%9C%20%EC%98%A4%EB%A5%98.png)

오류의 원인을 분석하기 위해 소스 코드를 살펴보자.

![](https://images.velog.io/images/kmk9502/post/4217786d-bb14-4531-ad66-e51440bb4427/High%20%EB%A0%88%EB%B2%A8%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

`fnmatch()` 함수를 사용해 page 파라미터를 저장한 `$file` 매개변수를 검증하여 파일 호출 필터링을 하고 있다. 위 코드를 해석하면 page 파라미터 값의 파일명이 `file`로 시작하지 않거나 `include.php (실습 페이지 최초 화면 주소)` 파일이 아닌 경우 에러 메시지를 출력하는 코드이다.

위 코드를 우회하기 위해서 `file로 시작하는 파일을 호출`하거나 PHP가 지원하는 `file://` 형식의 URL을 사용하여 로컬 파일 시스템에 접근한다. 

![](https://images.velog.io/images/kmk9502/post/2b2ed43f-6af1-42b7-b451-ea04afdbfb66/High%EB%A0%88%EB%B2%A8%20%EC%9A%B0%ED%9A%8C%EB%A1%9C%20%ED%8C%8C%EC%9D%BC%20%ED%98%B8%EC%B6%9C.png)

위 사진은 주소창에 `file:///etc/passwd`를 입력한 결과이다. `file://`로 인해 PHP는 내부 파일로 인식하고 명령을 실행한다.
