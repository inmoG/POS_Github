# Sample 02.exe 분석

## 분석 목적
- ### Sample 02.exe 파일을 분석 및 수정하여 'If Code!!' 문자열을 출력하라!

## 어셈블리 코드 분석

- ### **1. 문제**

  ![](https://images.velog.io/images/kmk9502/post/e123d61d-fe9f-4e1e-9a86-162878dfe786/%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EB%AC%B8%EC%A0%9C_%EC%B2%AB%20%EB%B2%88%EC%A7%B8.png)

  - 프로그램의 어떠한 문제로 인하여 'If Code!!' 문자열이 출력되지 않는다. 

- ### **2. main() 함수 찾기**
  
  ![](https://images.velog.io/images/kmk9502/post/90095e68-d68c-4657-8842-498e22ab7ba2/main%20%ED%95%A8%EC%88%98%20%EC%9C%84%EC%B9%98.png) 

  - 메모리 주소 : 0040100

  </br></br>

- ### **3. 프로그램 기능 파악**

    ![](https://images.velog.io/images/kmk9502/post/afc46be9-13e6-4ee4-a42c-4666a4a0ad1b/%ED%9D%A5%EB%AF%B8%EB%A1%9C%EC%9A%B4%20%ED%95%A8%EC%88%98%20%EB%B0%9C%EA%B2%AC.png)

    - **주목할 함수 찾기**
      - GetLocalTime
        - 현재 로컬의 날짜 및 시간을 검색하고 SYSTEMTIME 구조체에 시간정보를 저장한다.
        - SYSTEMTIME 구조체 구성
          - 년도, 월, 요일, 일, 시간, 분, 초, 미리초
    - **주목할 알고리즘 찾기**
      - 조건문
        - 함수 호출 다음, CMP 명령어로 [ESP+4]에서 7D5를 뺀 연산 결과를 바탕으로 조건문 점프를 실행하는 코드가 3개 발견되었다. 즉, 3개의 조건문이 존재한다.
      - 알고리즘 내 인자 값 분석
        - [ESP+4] : 해당 스택 주소에는 0x7E4 값이 있으며, 10진수로 환산하면 2020이라는 값이 도출된다.
        - 0x7D5 : 10진수로 환산하면 2005라는 값이 도출된다.
        - 0x0040106C : 해당 주소에는 함수 종료 명령어가 존재한다. 즉, JNZ(Jump Not Zero)의 조건에 만족하지 않으면 함수는 곧바로 종료된다.
        - [ESP+2] : 해당 스택 주소에는 0x0A 값이 있으며, 10진수로 10이라는 값이 도출된다.
        - [ESP+6] : 해당 스택 주소에는 0x0E 값이 있으며, 10진수로 14라는 값이 도출된다.
        - 0x20 : 10진수로 32라는 값이 도출된다.
    - **프로그램 기능 유추**
      - 현재의 시간이 2005년 0월 32일과 일치하는 근거가 있다면 'If Code!!'를 출력하는 프로그램일 것이다.
    - **문제**
      - 2005년 0월 32일은 현재 시간은 물론, 존재하지 않는 시간이다. 따라서 코드를 수정하지 않는다면 'If Code!!' 문자열을 출력할 수 없다.

</br></br>

- ### **4. 문제 해결**

    -  **첫 번째 방법**
        -  if 조건문을 '값이 같을 때 통과'가 아닌, '값이 다를 때 통과'로 바꾼다. </br>즉, JNZ  (함수종료주소)를 JE(Jump Equal)  (함수종료주소)로 바꾼다.

         ![](https://images.velog.io/images/kmk9502/post/fa69bbaf-6503-4b33-97b2-f84b2325d970/%EC%B2%AB%EB%B2%88%EC%A7%B8%20%EB%B0%A9%EB%B2%95_%EB%AA%85%EB%A0%B9%EC%96%B4%20%EB%B0%94%EA%BE%B8%EA%B8%B0.png)

   - **두 번째 방법**
     - CMP 비교문에서 2005, 0, 32를 2020, 10, 14의 16진수 형태로 치환한다.

     ![](https://images.velog.io/images/kmk9502/post/1441feca-dfc2-440a-9783-e44a1b1e76b7/%EB%91%90%20%EB%B2%88%EC%A7%B8%20%EB%B0%A9%EB%B2%95_%EC%9D%B8%EC%9E%90%20%EA%B0%92%20%EB%B0%94%EA%BE%B8%EA%B8%B0.png)

  - **세 번째 방법**
    - 무조건 점프인 'JMP  (If Code!! 출력주소)' 로 수정하여 바로 출력한다.

    ![](https://images.velog.io/images/kmk9502/post/b6656f85-2926-424b-bf1c-d54ccf62d9d8/%EC%84%B8%20%EB%B2%88%EC%A7%B8%20%EB%B0%A9%EB%B2%95_%EB%AC%B4%EC%A1%B0%EA%B1%B4%20%EC%A0%90%ED%94%84.png) 

  - **네 번째 방법**
    - Flag Register의 값을 바꾸어 조건문 실행을 막는다.

    ![](https://images.velog.io/images/kmk9502/post/355ddd12-9a09-4502-a19f-2b23ff5d348b/Zero%20%ED%94%8C%EB%9E%98%EA%B7%B8.png)

    - **Z 플래그 레지스터**
      - JNZ(Jump Not Zero) 명령어는 CMP 명령어로 두 개의 인자 값을 빼기 연산을 하여 나온 값이 0이 아닐 경우에만 설정한 주소로 건너뛴다(Jump). </br>이 때 CMP의 결과 값이 0일 경우, 위 사진의 **Z 플래그 레지스터**가 1로 설정된다. JNZ는 이 플래그 정보를 바탕으로 CMP 연산 결과가 0인지, 1인지 판단할 수 있다.
       
    ![](https://images.velog.io/images/kmk9502/post/3a981a27-daea-494a-8808-d9bd8d85644e/Zero%20%ED%94%8C%EB%9E%98%EA%B7%B8%20%EC%88%98%EC%A0%95.png) 

    - Z 플래그 레지스터 값을 1로 변경하여 JNZ를 속인다.
     
    ![](https://images.velog.io/images/kmk9502/post/dbf77fd0-0e4d-44a1-b56a-0f7cb96c431d/%EC%88%98%EC%A0%95%20%EA%B2%B0%EA%B3%BC.png)  

    -  실행 결과, Z 플래그 레지스터를 조작하여 JNZ를 완벽히 속였다는 것을 알 수 있다.

</br></br></br></br>

# Sample 03.exe 분석

## 분석 목적
- ### Sample 03.exe 파일을 수정하여 'For Code!!' 문자열을 출력하도록 하라

## 어셈블리 코드 분석

- ### **1. 문제**

  ![](https://images.velog.io/images/kmk9502/post/babafa92-69e8-4757-9c20-e767cbb4b724/Sample%2003.exe%20%EB%AC%B8%EC%A0%9C.png)

  - 프로그램이 어떠한 문제로 인하여 10칸의 공백이 출력된다.

- ### **2. main() 함수 찾기**

  ![](https://images.velog.io/images/kmk9502/post/d81c31b0-41b3-44f9-8b0e-10f2e1be31c6/main%ED%95%A8%EC%88%98%20%EC%9C%84%EC%B9%98.png)

  - Sample 02.exe 파일과 같은 위치에 main() 함수 존재

- ### **3. 프로그램 기능 파악**

  ![](https://images.velog.io/images/kmk9502/post/23088420-3de7-4924-bcf3-76ec6e0afbf3/%EC%9D%98%EB%AF%B8%EC%9E%88%EB%8A%94%20%EC%BD%94%EB%93%9C.png)

  - **주목할 함수 찾기**
    - 0x0040104E에 위치한 함수
    - 함수의 이름이 적혀있지 않아 함수의 역할을 알 수 없음
  - **주목할 알고리즘 찾기**
    - **for 반복문**
      - ESI에 저장된 값이 0x14 미만일 때 0x00401043에서 0x0040105A 구간을 반복한다.
    - **알고리즘 분석**
      - 1. 변수 ESI에 0x0A(10진수 10)를 저장
      - 2. 인자 값 ECX에 ESP+ESI+0x08에 위치한 값을 저장한다.
       
           ![](https://images.velog.io/images/kmk9502/post/93a3197e-caaf-4def-b9d3-7f2e445e0b52/ECX%EC%97%90%20%EC%A0%80%EC%9E%A5%EB%90%98%EB%8A%94%20%EA%B0%92.png) 

           - ESP+ESI+0x08 = 0x0012FE40+0x0A+0x08 = 12FE52
       - 3. 인자 값 ECX와 변수 타입 %c를 스택에 저장하여 호출한 함수가 사용할 수 있도록 한다.
         - %c는 주로 printf("%c", [문자열이 저장된 배열]) 형태로 사용되며 배열에 저장된 문자열의 문자를 하나씩 읽어 출력하는 변수 타입이다.
       - 4. 함수를 호출한다.
         - 변수 타입을 사용하고 아스키 코드 값을 변수로 사용하며 콘솔에 출력하는 이 함수는 아마도 **printf();** 함수일 것이다.
       - 5. ADD 명령어로 함수 호출에 사용한 2개의 인자 값 스택을 정리한다.
       - 6. ING 명령어로 ESI 값을 1만큼 증가시킨다. 
         - ESI는 0x0A에서 0x0B가 된다.
       - 7. CMP 명령어로 ESI와 0x14를 비교한 결과를 플래그 레지스터에 반영한다.
       - 8. JL(Jump if Less) 명령어로 ESI 값이 0x14보다 작다면 해당 주소로 점프한다.
       - 9. 반복문을 완료한 후 스택을 정리하고 프로그램을 종료한다.
  - **프로그램 기능 유추**
     - for 반복문과 %c, printf() 함수를 사용하여 배열에 저장된 문자열을 하나씩 출력하는 프로그램일 것이다.
   - **문제**
     - 인자 값 ECX에 저장되는 값의 위치가 비정상적이다. ECX의 값을 문자열 시작 위치인 0x0012FE48 주소로 변경해야 한다.
 - ### **4. 문제 해결**

    - **첫 번째 방법**

      - 0x00401030 주소에서 ESI에 저장되는 값을 0으로 수정하여 ECX에 문자열의 시작 주소인 0x0012FE48을 저장한다.

      ![](https://images.velog.io/images/kmk9502/post/be2b4763-ba06-4359-ae5d-372b70a01820/%EC%B2%AB%20%EB%B2%88%EC%A7%B8%20%EB%AC%B8%EC%A0%9C%ED%95%B4%EA%B2%B0%20%EB%B0%A9%EB%B2%95.png) 

    - **두 번째 방법**
      - 인자 값 %c를 For Code!!의 주소로 치환하고 CMP ESI,14를 CMP ESI,0A로 변경해 반복수를 1번으로 수정
      - 문제 : %c를 이용해 하나의 문자씩 출력하지 않는다. 즉, 프로그램의 본래 의도에 반하는 방법이다.

      ![](https://images.velog.io/images/kmk9502/post/82e74289-a6d0-4f4b-bd4e-3061754d86f3/%EB%91%90%20%EB%B2%88%EC%A7%B8%20%EB%AC%B8%EC%A0%9C%20%ED%95%B4%EA%B2%B0%20%EB%B0%A9%EB%B2%95.png) 