# Brute Force Attack

Brute Force 공격이란 무차별 대입 공격으로서 사용자 인증을 통과 또는 특정 암호를 풀 수 있는 모든 값을 대입하는 공격이다. 대부분의 인증 방식은 이론적으로 Brute Force 공격에 안전하지 못하며, 충분한 시간만 주어진다면 암호화된 정보를 해독할 수 있다.

# Brute Force 공격에 취약한 구조

- 디폴트 패스워드
- 쉬운 패스워드
- 설계 상 인증 문제
  - 패스워드 실패 시 잠금 기능 X
    로그인 시 임계 값을 설정하여 인증시도가 연속으로 실패하면 일정 시간 잠기거나 CAPCHA 코드 입력을 요구하는 등 공격을 지연시켜야 한다.
  - 오류 메시지
    아이디와 패스워드 입력 시 "아이디가 존재하지 않습니다" 또는 "패스워드가 일치하지 않습니다"와 같은 오류 메시지는 아이디가 DB에 존재하는지, 아이디는 일치하고 패스워드는 일치하지 않는지 여부를 알 수 있어 공격 시간을 단축시켜준다. 따라서 오류 메시지를 "아이디 또는 패스워드가 일치하지 않습니다"와 같이 구현해야 한다.

## 공격

칼리 리눅스 2019.1 버전을 사용하며 공격 대상은 `DVWA web application`이다.

![](https://images.velog.io/images/jjewqm/post/0f487d59-4da1-4337-a4d5-f3e7826a9d29/image.png)

`admin/admin`으로 로그인 결과 `username and/or password incorrect` 메시지가 출력된다. 따라서 `admin` 아이디 존재여부를 확인할 수 없다. `password incorrect` 메시지가 출력되었다면 `admin` 계정이 존재한다고 추측 가능하다.

### BurpSuite

`BurpSuite`는 웹 프록시 도구로 웹 해킹 시 주로 사용하는 도구이다. `Brute Force` 공격은 로그인 시도 패킷을 만들어야 하므로 `BurpSuite`를 사용하겠다. 프록시 도구를 사용하려면 브라우저의 프록시 설정을 활성화 하거나 프록시 확장프로그램을 사용해야 한다. 본 문서에서는 Firefox의 `FoxyProxy` 확장프로그램을 사용한다.

![](https://images.velog.io/images/jjewqm/post/f6f8f18f-25a6-437c-a733-c870b1ec0fbd/image.png)

설정 후 `proxy` 버튼을 클릭하면 프록시가 활성화 된다.

![](https://images.velog.io/images/jjewqm/post/baa85ce2-91c4-4667-ad9f-7b4cf9f1eebc/4.png)

`BurpSuite`를 실행하여 proxy 탭 하위의 Options탭에서 Running 부분을 체크한다.

![](https://images.velog.io/images/jjewqm/post/b7bdc510-46fd-43d6-9d6d-a47d141135a1/5.png)

체크 후 proxy 탭 하위의 Intercept탭에서 Intercept is on 부분이 on으로 설정되어 있는지 확인한다.

![](https://images.velog.io/images/jjewqm/post/92a37546-c67f-46d5-8cef-9f0e5e94b173/6.png)

DVWA Brute Force 페이지에서 admin/1234를 입력한 뒤에, Login 버튼을 클릭한다.

![](https://images.velog.io/images/jjewqm/post/88ad0214-3e60-455e-9889-3313beedec84/image.png)

Raw탭 아래의 HTTP Message Display 창에서 마우스 우클릭 후 `Send to Intruder` 메뉴를 클릭한다. 또는 단축키 `Ctrl+I`를 입력한다.

![](https://images.velog.io/images/jjewqm/post/845658e1-3bc2-4553-9cf9-7e47ed660b46/8.png)

Intruder 탭의 Positions 탭으로 이동한다. 로그인 인자 값으로 넘어가는 username, password, login, PHPSESSID 등의 값 앞뒤로 `§`문자와 음영이 표시된다. Clear 버튼을 클릭하면, 음영과 `§` 문자가 사라진다.

![](https://images.velog.io/images/jjewqm/post/aeefc0e6-0bf0-4a0e-a9eb-674857b806d5/9.png)

공격을 실행하기 위해 패스워드 값을 마우스로 드래그 한 뒤, Add 버튼 클릭 시, password 인자 값에만 `§`문자가 표시된다.

![](https://images.velog.io/images/jjewqm/post/81a65277-17b7-4756-8f7e-c646662d3dd7/image.png)

Payloads 탭으로 이동해 값을 설정한다. Brute Force 공격을 위한 세부설정 후 start attack을 클릭하면 공격이 진행된다. 설정내용은 다음과 같다.

![](https://images.velog.io/images/jjewqm/post/0a3040e0-4de3-4628-9acb-10171cc53c53/image.png)

|     구분      |                                          내용                                          |
| :-----------: | :------------------------------------------------------------------------------------: |
|  Payload set  |      `§`를 구분하는 값, 파라미터 2개에 `§`문자를 넣었다면 payload set 을 2로 설정      |
| Payload type  | 공격 유형을 설정한다. Simple list, Runtime file, Brute forcer, Null payloads 등이 존재 |
| Character set |                                 공격 시도 문자열 설정                                  |
|  Min length   |                            Brute Force 공격 최소 길이 설정                             |
|  Max length   |                            Brute Force 공격 최대 길이 설정                             |

Brute Force 공격이 시작되면 payload 값, 로그인 시도 중인 패스워드 값이 나타난다. 공격에 성공한 패킷은 `Length`값이 다르다. 로그인 성공과 실패에 대한 html 반환 값이 다르기 때문이다.

![](https://images.velog.io/images/jjewqm/post/65915651-9d15-4a63-919c-00df9de83c99/12.png)

로그인에 실패한 Response 패킷은 아래와 같이 `User name and/or password incorrect` 메시지를 출력한다.

![](https://images.velog.io/images/jjewqm/post/7f9dc930-9b69-4f86-9163-74bfb3e3ed1b/13.png)

로그인에 성공한 패킷은 `Welcome to the password protected area admin` 메시지를 출력한다.

![](https://images.velog.io/images/jjewqm/post/8890fb7c-434a-4224-9c8d-84e8b6ffe5be/14.png)

![](https://images.velog.io/images/jjewqm/post/b4efd2b1-25d5-44c5-8d92-a025791b3f93/15.png)
