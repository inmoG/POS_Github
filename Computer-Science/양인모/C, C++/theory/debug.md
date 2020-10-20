# Debug

- bug
  프로그램이 의도하지 않은 동작을 일으키는 행위
- debuging

  코드에 있는 버그를 식별하고 고치는 과정

- debugger

  버그(bug)를 제거하는(de-) 도구, 프로그램의 내부 상황을 손쉽게 파악할 수 있어서 버그 찾는데 도움을 준다.

## Visual Studio debugger

디버거를 사용하기 전에 솔루션 구성을 확인해야한다. `Visual Studio` 상단 메뉴에서 로컬 Windows 디버거 왼쪽 부분이 `Debug`와 `x86`으로 선택되어 있는지 확인한다. 만약 다른 것으로 선택 되었다면 `Debug`와 `x86`을 선택한다.

![디버거 솔루션구성.png](https://images.velog.io/post-images/jjewqm/e7c5de50-df21-11e9-847e-e10a62b4542e/디버거-솔루션구성.png)

main 함수를 여는 중괄호 `{` 가 있는 줄에서 마우스 오른쪽 버튼을 클릭한다.
메뉴가 나오면 중단점(B) > 중단점 삽입(R)을 선택한다.
또는 `{` 가 있는 줄에서 F9를 누른다.

![디버거 중단점 .png](https://images.velog.io/post-images/jjewqm/f445f110-df21-11e9-8288-7941d0147846/디버거-중단점-.png)

선택하면 아래 그림처럼 빨간색 원이 표시된다. 이 원은 중단점(브레이크 포인트)를 의미하며 여기서 실행을 멈추라는 뜻이다.

![디버거 중단점 확인.png](https://images.velog.io/post-images/jjewqm/436c0be0-df21-11e9-90eb-0f75a4a4f6a6/디버거-중단점-확인.png)

중단점이 생성되었으면 F5 버튼을 눌러 디버깅을 시작한다.
빨간색 원이 노란색 화살표로 변하며 프로그램이 중단된다.

![디버깅 시작.png](https://images.velog.io/post-images/jjewqm/b8914100-df22-11e9-8288-7941d0147846/디버깅-시작.png)

F10 버튼을 누르면 노란색 화살표가 한 줄 아래로 이동한다. 화면 아래쪽의 자동부분을 보면 변수 num1이 생성되었다.

![디버깅 1.png](https://images.velog.io/post-images/jjewqm/2303ece0-df23-11e9-8288-7941d0147846/디버깅-1.png)

아직 num1에 값이 생성되지 않았다.
F10을 한번 더 눌러 값을 생성한다.

![디버깅 2.png](https://images.velog.io/post-images/jjewqm/5f2aadc0-df24-11e9-90eb-0f75a4a4f6a6/디버깅-2.png)

num1의 값 10이 생성되었다.
num1 변수에 마우스를 가져다 놓으면 해당 변수에 저장된 값을 확인할 수 있다.
F10을 계속 눌러 printf()함수를 실행해 명령프롬프트에도 숫자가 한 줄씩 출력된다.

![printf결과.png](https://images.velog.io/post-images/jjewqm/5f190fa0-df26-11e9-91a3-3394021e1fd1/printf결과.png)

노란색 화살표는 현재 줄을 실행하기 위해 대기한다는 뜻이다. 즉 마지막 printf는 실행 대기중이다.
디버깅을 끝내려면 Shift + F5 키를 누르면 된다.

### 디버깅 단축키

- 중단점 삽입/삭제: F9

- 디버깅 시작: F5

- 디버깅 중지: Shift+F5

- 프로시저 단위 실행: F10

- 한 단계씩 코드 실행: F11
