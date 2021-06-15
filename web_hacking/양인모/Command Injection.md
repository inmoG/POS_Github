`Command Injection` 공격이란 사용자가 입력하는 인자 값을 조작해 OS 명령을 실행하는 공격기법이다. 웹을 통해 시스템 명령어를 실행하게 되며, 특정 명령어 실행에 성공하면 작게는 파일정보 유출 크게는 시스템 장악까지 가능하다. `Command Injection`이 발생할 경우 현재 Command를 실행시키는 웹 어플리케이션의 권한만큼 해당 서버에서 권한을 획득할 수 있다.

# 분석

Enter an IP address에 IP를 입력하니 `ping`명령이 실행되었다. `ping`은 쉘을 통해 시스템 명령을 실행해야 한다. 하지만 웹에서 시스템 명령이 실행된다는 것은 운영체제에게 시스템 명령을 호출한다는 의미로 `Command Injection` 취약점이 있다고 추측할 수 있다.

![](https://images.velog.io/images/jjewqm/post/e83c1f09-ce30-4889-9f94-27b5ee8c8adf/18.png)

`Command Injection` 취약점이 있는지 소스코드를 확인하겠다.

![](https://images.velog.io/images/jjewqm/post/10e74a49-dbdf-408e-88f7-b0667166cbe3/19.png)

`shell_exec()` 함수는 쉘을 통해 명령을 실행하고 전체 출력을 문자열로 반환하는 함수이다. 해당 함수를 사용해 시스템 명령이 실행된다 추측할 수 있다.

## Command Injection 취약함수

|  언어  |                                                         함수                                                          |
| :----: | :-------------------------------------------------------------------------------------------------------------------: |
|  Java  |                                  System.\*, 특히 System.runtime 취약, Runtime.exec()                                  |
| C/C++  |                                           system(), exec(), ShellExecute()                                            |
| python |                    exec(), eval(), os.system(), os.popen(), subprocess.popen(), subprocess.call()                     |
|  Perl  |                                          open(), sysopen(), system(), glob()                                          |
|  php   | exec(), system(), passthru(), popen(), rquire(), include(), eval(), preg_replace(), shell_exec(), proc_open(), eval() |

### 메타문자

쉘에는 한 줄에 여러 명령어를 실행하는 등의 쉘 사용자 편의성을 위해 제공하는 특수 문자들이 존재한다. 시스템 명령이 수행된다면 특수문자를 활용해 `Command Injection` 공격이 가능하다.

|                           메타문자                           |                                                                            설명                                                                            |
| :----------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------------------: |
| `|**명령어 치환**` 안에 들어있는 명령어를 실행한 결과로 치환 |
|                             \$()                             |                                      **명령어 치환** `$()` 안에 들어있는 명령어를 실행한 결과로 치환, 중복 사용 가능                                       |
|                              &&                              |                   **명령어 연속 실행** 한 줄에 여러 명령어를 사용하고 싶을 때 사용. 앞 명령어에서 에러가 발생하지 않아야 뒷 명령어 실행                    |
|                             \|\|                             |                       **명령어 연속 실행** 한 줄에 여러 명령어를 사용하고 싶을 때 사용. 앞 명령어에서 에러가 발생해야 뒷 명령어 실행                       |
|                              ;                               | **명령어 구분자** 한 줄에 여러 명령어를 사용하고 싶을 때 사용. `;` 은 단순히 명령어 구분을 위해 사용하며, 앞 명령어의 에러 유무와 관계 없이 뒷 명령어 실행 |
|                              \|                              |                                                  **파이프** 앞 명령어 결과가 뒷 명령어 입력으로 들어간다.                                                  |
|                            그 외                             |                                                            `.`, >, >>, &>, >&, <, {}, ?, \*, ~                                                             |

### 공격

`low` 단계에서 `;` 메타문자와 `ls-al` 명령어를 결합해 공격을 시도하니 `ping`과 `ls`명령어가 실행되어 현재 디렉토리 내 파일들을 출력한다. `;` 메타문자 외 다른 문자를 사용해 공격을 진행하겠다.

![](https://images.velog.io/images/jjewqm/post/aa748794-1e84-4e87-94c5-86c5018d4887/image.png)

- &&

  ![](https://images.velog.io/images/jjewqm/post/219c7830-ac8e-4681-99cc-765fc13b7682/image.png)

- |

  ![](https://images.velog.io/images/jjewqm/post/7a4dd40a-aed8-41ba-9257-d1686cea0695/image.png)

- ||

  ![](https://images.velog.io/images/jjewqm/post/2ce7a461-bae7-482f-bfab-92aa1c01f7c8/image.png)

#### Medium level

`medium level`에서 `;ls`, `;pwd`, `&&cat /etc/passwd` 명령이 실행되지 않는다. 소스코드를 확인하니 `&&`와 `;`를 공백으로 치환한다.

![](https://images.velog.io/images/jjewqm/post/75816a19-d0e4-4db9-a657-54f350e683e6/24.png)

`&&`, `;` 외 다른 메타문자를 사용해 공격을 진행한다. `&`와 `|`를 사용해 공격이 성공하였다.

![](https://images.velog.io/images/jjewqm/post/8f508f6e-e9d2-421e-9712-d21d7573ae10/image.png)

#### high level

`high level`에서는 사용 가능한 특수문자 대부분을 필터링한다. 이제 우회 방법은 필터링되는 문자의 허점을 찾는 것이다. 즉 개발자의 실수를 찾아야 한다.

![](https://images.velog.io/images/jjewqm/post/835dbd37-5b84-4fca-9c9f-dc4f7f4f3ba2/27.png)

특수문자 대부분을 필터링하였지만 `|` 문자 필터링을 실수해 공격에 성공하였다.

![](https://images.velog.io/images/jjewqm/post/b63216c2-02b4-49a5-9f4b-0998f47cdd80/28.png)
