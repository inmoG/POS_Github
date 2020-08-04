# 개념

`File Upload`는 게시판이나 3rd-party 등의 웹 애플리케이션 등에서 파일을 업로드 할 수 있는 기능을 악용한 공격으로써,</br> `파일 확장자`에 업로드 제한을 하지 않아 발생한다. </br>
공격자는 악성 파일을 업로드하여 희생자 측 서버의 명령을 실행하거나 파일을 조작할 수 있다. </br>
악성파일 중 `웹쉘`의 경우, 파일 업로드 대상 디렉토리에 `실행 권한`이 있다면 웹 브라우저에서 다른 서버 사이드 언어처럼 실행할 수 있다.

# File Upload 공격 유형

|구분|설명|
|:--:|:--|
|파일 확장자 우회|- 서버 우회 (Server side script) </br>- 클라이언트 우회(client side script)
|취약점|- 정상 확장자 (JPG, PNG 등)를 이용한 우회</br>- WEB / WAS 취약점 악용 우회</br>- Application (OS, DBMS, Editor 등) 취약점 악용 우회|
| |

# 웹쉘 특징

|구분|설명|
|:--:|:--|
|China Chopper|- 비밀번호 무차별 공격을 포함한 명령 및 제어기능이 존재|
|WSO|- "Orb by Web Shell"의 약자로 숨겨진 로그인 폼이 포함된 오류 페이지로 가장할 수 있음|
|C99|-추가기능을 갖춘 WSO 쉘 버전</br>- 서버의 보안 측정을 표시할 수 있으며, 자체 삭제기능을 가지고 있음|
|B374K|- 프로세스 보기 및 명령 실행과 같은 공통 기능을 갖춘 PHP 기반 웹쉘|
||

# 공격
## Low 레벨

다운로드한 웹쉘을 업로드하면 오류가 발생한다.

![](https://images.velog.io/images/kmk9502/post/933cdc5e-eac2-4b77-8698-9b4b1c46b81d/%EC%9B%B9%EC%89%98%20%ED%8C%8C%EC%9D%BC%20%EC%97%85%EB%A1%9C%EB%93%9C%20%EC%8B%A4%ED%8C%A8.png)

소스 코드를 확인해보자. 65번째 라인에 `파일의 최대 사이즈 값`이 100,000으로 설정되어 있다.

![](https://images.velog.io/images/kmk9502/post/9012d3f8-5f16-4e28-a7d2-2083f98e3750/%EC%9B%B9%ED%8E%98%EC%9D%B4%EC%A7%80%20%EC%86%8C%EC%8A%A4%EC%BD%94%EB%93%9C.png)

프록시 도구인 BurpSuite를 활용하여 파일 업로드 패킷의 `MAX_FILE_SIZE`를 `500,000`으로 조작한다. </br>
그 결과, 웹쉘 파일 업로드에 성공하였다.

![](https://images.velog.io/images/kmk9502/post/4d85b0cf-24f5-4c24-8a21-bd1e3d909b80/500000%EC%9C%BC%EB%A1%9C%20%EC%88%98%EC%A0%95.png)![](https://images.velog.io/images/kmk9502/post/83d12ab2-9247-4923-83e2-aa8a8213ed71/%EC%9B%B9%EC%89%98%20%ED%8C%8C%EC%9D%BC%20%EC%97%85%EB%A1%9C%EB%93%9C%20%EC%84%B1%EA%B3%B5.png)

위의 출력된 문자열 중 `../../hackable/uploads/`는 현재 웹 페이지 주소에서의 상대경로를 의미한다. </br>현재 페이지의 주소를 기반으로 알 수 있는 업로드된 파일의 주소는 `http://localhost:81//hackable/uploads/b374k-3.2.3.php`가 된다. </br>
이제 웹쉘을 실행하기 위해 주소창에 해당 경로와 파일명을 입력하여 웹쉘을 실행하자.

![](https://images.velog.io/images/kmk9502/post/c2c40c52-4f24-4eb3-9d94-2bc53c5343c4/%EC%9B%B9%EC%89%98%20%EC%A0%91%EC%86%8D%20%EC%8B%9C%20%EC%9D%B8%EC%A6%9D%20%ED%8E%98%EC%9D%B4%EC%A7%80.png)

웹쉘의 인증과정을 통과하면 웹쉘 실행 화면이 출력된다. 이 단계에서는 `웹 프로세스 권한`을 통해 파일 생성, 수정, 삭제 등의 다양한 악성행위를 수행할 수 있고, 데이터베이스에도 접근이 가능하다.

![](https://images.velog.io/images/kmk9502/post/2c15e772-21aa-4285-a2d8-bdf22d8c5813/%EC%9B%B9%EC%89%98%20%EC%8B%A4%ED%96%89%20%ED%99%94%EB%A9%B4.png)
</br></br></br></br>
## Medium 레벨

Low 레벨에서 통했던 File Upload 공격이 Medium 레벨에서는 오류가 발생한다.

![](https://images.velog.io/images/kmk9502/post/1e26ebae-d753-49ed-8200-03becbb618ab/Medium%20%EB%A0%88%EB%B2%A8%20%ED%8C%8C%EC%9D%BC%20%EC%97%85%EB%A1%9C%EB%93%9C%20%EC%8B%9C%EB%8F%84.png)

오류 원인 분석을 위해 소스 코드와 패킷의 내용을 살펴보자. 아래 사진과 같이 `Content-Type`의 값이  `파일 확장명 필터링` 구문에 의해 필터링 되는 것을 알 수 있다. 
![](https://images.velog.io/images/kmk9502/post/2b7b6826-9a70-47b2-bcf6-323375f03500/Medium%20%EC%86%8C%EC%8A%A4%20%EB%82%B4%20%ED%99%95%EC%9E%A5%EC%9E%90%20%ED%95%84%ED%84%B0%EB%A7%81%20%EA%B5%AC%EB%AC%B8.png)![](https://images.velog.io/images/kmk9502/post/79194465-af00-4564-b395-81fb5d63048a/%ED%8C%8C%EC%9D%BC%20%EC%97%85%EB%A1%9C%EB%93%9C%20%ED%8C%A8%ED%82%B7%20%EC%BA%A1%EC%B3%90_%EC%88%98%EC%A0%95.png)

필터링을 우회하기 위해 패킷의 `Content-Type`을 정상 패킷으로 위조한다. 이때 웹쉘 생성 도구인 `weevely`를 이용한다.</br></br>

`weevely`로 생성한 파일을 업로드한 뒤 프록시 도구로 패킷 내의 `Content-Type`의 값을 `image/png`로 위조한 뒤 다시 전송한다. 
![](https://images.velog.io/images/kmk9502/post/ca802693-5ea9-4d90-bc9c-ec556b0db500/Content%20Type%20%EC%88%98%EC%A0%95.png)
![](https://images.velog.io/images/kmk9502/post/9281a736-1a51-47fa-b2f6-65e9f1eb617c/Medium%20%EB%A0%88%EB%B2%A8%20%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)

그 결과, 서버는 해당 패킷을 정상 패킷으로 간주하고 참조한다.
</br></br>
`weevely` 명령을 통해 서버에 업로드 한 웹쉘에 접속한 결과이다. 성공적으로 접속한 것을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/ffdeec42-2645-4307-98fc-3f09c808a60d/%EC%97%85%EB%A1%9C%EB%93%9C%ED%95%9C%20%EC%9B%B9%EC%89%98%EC%9D%84%20%ED%86%B5%ED%95%B4%20%EC%84%9C%EB%B2%84%EC%97%90%20%EC%A0%91%EC%86%8D.png)
</br></br></br></br>
## High 레벨

Medium 레벨처럼 Content-Type만을 변조해서는 공격이 되지 않는다. High 레벨의 소스코드를 확인하자.
![](https://images.velog.io/images/kmk9502/post/36b3122f-3ded-42aa-9eda-cbb14172080a/High%20%EB%A0%88%EB%B2%A8%20%EC%86%9F%EC%8A%A4%20%EC%BD%94%EB%93%9C.png)

위 사진처럼 실제 확장자가 `PNG` 혹은 `JPEG`인지 체크하거나 이미지 파일의 헤더를 확인하는 로직이 보인다.</br> </br>이를 우회하기 위해 패킷의 `Content-Type` 하단부에 png 파일의 시그니처인 `PNG`를 추가하여 확장자와 파일 헤더만 이미지 파일의 형식을 따르게 해 필터링 코드를 우회한다. </br>
물론, 파일 내용은 웹쉘이다. 이 우회 기법에는 WSO 웹쉘을 사용한다.

우선, 생성한 파일의 확장자를 `png` 형태로 인식시키기 위해 파일 확장자를 `.png`로 변경한다.

![](https://images.velog.io/images/kmk9502/post/df27c7b0-102c-4943-845a-cf3fe9fc473d/%ED%99%95%EC%9E%A5%EC%9E%90%20%EB%B3%80%EA%B2%BD.png)

BurpSuite에서 Content-Type 하단부에 `png` 파일의 시그니처인 `PNG`를 추가한다.

![](https://images.velog.io/images/kmk9502/post/b9ac917f-ed09-4000-83a9-3aa137f6e133/PHP%20%EC%8B%9C%EA%B7%B8%EB%8B%88%EC%B2%98%20%EC%B6%94%EA%B0%80.png)![](https://images.velog.io/images/kmk9502/post/45478703-8873-4150-827a-bafd3538bbfb/High%20%EB%A0%88%EB%B2%A8%20%EA%B3%B5%EA%B2%A9%20%EC%84%B1%EA%B3%B5.png)

그 결과, 필터링을 우회하여 웹쉘이 업로드 되었다.</br></br>

웹쉘 파일을 실행하기 위해서 `File Inclusion` 취약점을 활용하여 `png확장자`로 된 웹쉘을 실행한다. </br>
`File Inclusion` 취약점을 활용하는 이유는 웹쉘 확장자가 `png`로 되어있어 서버 내 파일에 접근하지 않고서 실행하면 오류가 발생하기 때문이다. 그 결과는 아래와 같이 성공한 것을 확인할 수 있다.

![](https://images.velog.io/images/kmk9502/post/48ccf67a-2106-4b9c-b95c-49ee194b5268/File%20Inclusion%20%EC%B7%A8%EC%95%BD%EC%A0%90%20%EC%9D%91%EC%9A%A9%20File%20Upload%20%EA%B3%B5%EA%B2%A9.png)

해당 페이지에서는 시스템 권한을 가지고 다양한 악성행위를 수행하거나 파일 생성 / 수정 / 실행 / 업로드 등이 가능하다.