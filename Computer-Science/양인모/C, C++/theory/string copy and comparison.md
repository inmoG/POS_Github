# 문자열

`string s = "EMMA";`

문자열은 문자의 배열이다. s[0], s[1], s[2] 같이 하나의 문자가 배열의 한 부분을 나타낸다. 마지막 `\0`은 0으로 이루어진 바이트로, 문자열 끝을 표시한다. **변수 s**는 문자열을 가리키는 포인터다. 정확히는 문자열의 첫번째 문자, 즉 주소 0X123에 있는 s[0]을 가리킨다.

## 문자열 비교

```c
#include <stdio.h>

int main(void)
{
    char *s = "EMMA";
    printf("%p\n", s);
}
```

s라는 포인터 값, **"EMMA"** 문자열 가장 첫 값인 **"E"**에 해당하는 메모리 주소를 출력한다. 아래 코드와 같이 문자열은 첫번째 문자를 시작으로 메모리상에서 바로 옆에 하나씩 저장된다. 즉 문자(char)는 1바이트이므로 첫 번째 문자 주소값을 하나씩 증가시키면 다음 문자 주소에 저장된 값을 출력할 수 있다.

```c
printf("%p\n", &s[0]); // 문자열 첫 번째 문자에 해당하는 주소값
printf("%p\n", &s[1]); // 문자열 두 번째 문자에 해당하는 주소값
printf("%p\n", &s[2]); // 문자열 세 번째 문자에 해당하는 주소값
printf("%p\n", &s[3]); // 문자열 네 번째 문자에 해당하는 주소값
```

```c
printf("%c\n", *s); // E
printf("%c\n", *s+1); // M
printf("%c\n", *s+2); // M
printf("%c\n", *s+3); // A
```

문자열을 비교할 때도 문자열이 저장된 변수를 바로 비교하게 되면 **그 변수가 저장되어 있는 주소가 다르기 때문에** 다르다는 결과가 나온다. 따라서 정확한 비교를 위해서는 실제 문자열이 저장되어 있는 곳으로 이동해, 각 문자를 하나씩 비교해야 한다.

## 문자열 복사

```c
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void
{
    string s = get_string("s: ");
    string t = s;

    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);
}
```

입력값으로 "string"을 주면 s와 t 모두 "String"을 출력한다. 왜냐하면 s 변수에는 "string" 문자열이 아닌 문자열이 있는 메모리 주소가 저장되기 때문이다. **string s**는 **char \*s(포인터 변수)**와 동일한 의미이다. 따라서 t는 **메모리 주소를 복사해 s와 동일한 주소를 가리키며** t 값을 수정하면 s에 그대로 반영된다.

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1); // s 문자열 길이 + "\n" 문자

    for(int i = 0, n = strlen(s); i < n + 1; i++)
    {
        t[i] = s[i];
    }

    t[0] = toupper(t[0]);

    pritnf("s: %s\n", s);
    printf("t: %s\n", t);
}
```

이 코드는 `malloc`함수를 이용해 t를 정의한다. `malloc`함수는 정해진 크기 만큼 메모리를 할당하는 함수이다. for문을 돌면서 s 문자열 배열에 있는 문자 하나씩 t 배열에 복사해 출력하면 결과 값이 다르다. 왜냐하면 for문을 통해 s와 t 변수에 저장된 값은 같으나 가리키는 주소값이 다르기 때문이다.
