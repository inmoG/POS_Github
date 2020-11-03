# __조건문과 루프__
```
counter = counter + 1;
```
```
counter += 1;
```
```
counter ++;
```
변수(counter)의 값을 1씩 증가시키는 뜻이며, 같은 표현이다.

## __조건문__
```
ex)

if(x < y)
{
    print("x is less than y/n");
}
```
x가 y보다 작으면 `print("x is less than y/n");` 를 출력하라는 뜻이다.


else를 이용해 처음 조건이 아닌 경우에도 어떤 것을 수행하라라고 적어줄 수 있다.
```
if (x < y)
{
    print("x is less than y/n");
}
else
{
    print("x is not less than y/n");
}
```
else if를 통해 조건을 추가할 수도 있다.

```
if (x < y)
{
    print("x is less than y/n");
}
else
{
    print("x is not less than y/n");
}
else if (x == y)
{
    printf("x is equal to y/n");
}
```

## __루프(loop)__
while or for 문을 통해 루프를 구현할 수 있다.
### __while문__
```
while (true)
{
    printf("hello, world\n");
}
```
특정 횟수만큼 작업을 수행하려면,
```
int i = 0;
while (i < 50)
{
    printf("hello, world\n");
    i ++;
}
```
또는 사용자가 원하는 횟수를 수행하기 위해서는,
```
int i = 0;
int j = get_string(int)
while (i < j)
{
    printf ("hello, world\n");
    i ++;
}
```
### __for문__
for() 안에 각 변수 초기화; 변수 조건; 변수 증가에 해당하는 코드를 넣어서 간단하게 표현할 수 있다.
즉, 가장 먼저 정수 값을 가지는 i라는 변수를 0으로 초기화하고, i가 50인지 매번 검사를 하고, 이를 만족하면 { } 안의 내용을 수행한 후에,  i를 1씩 증가시킨다는 의미이다.
```
for (int i = 0; i < 50;> i ++)
{
    printf("hello, world\n");
}