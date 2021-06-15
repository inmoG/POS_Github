#include <stdio.h>

int main(void)
{
	/*
	int add = 3 + 7;
	printf("%d\n", add);
	
	printf("%d + %d = %d\n", 30, 70, 30 + 70);
	printf("%d * %d = %d\n", 10, 5, 10 * 5);
	printf("%f + %f = %f\n", 3.5, 4.3, 3.5 + 4.3);
	printf("%d, %d, %d, %d", a, b, c, d);
	
	int a, b;
	int a;
	double b;
	a = 10;
	b = 3;

	/*printf("a + b 는 : %d \n", a + b);
	printf("a - b 는 : %d \n", a - b);
	printf("a * b 는  : %d \n", a * b);
	printf("a / b 는 : %d \n", a / b);
	printf(" a %% b 는 : %d \n", a % b);
	printf("a + b 는 : %d \n", a + b);
	
	int a = 3;
	a = a+3;
	printf("a 의 값은 : %d \n", a);
	

	int a = 1, b = 1, c = 1, d = 1;
	a = a + 1;
	printf("a : %d \n", a);
	b += 1;
	printf("b : %d \n", b);
	++c;
	printf("c : %d \n", c);
	d++;
	printf("d : %d \n", d);
	

	int a, b, c, d;
	a = b = c = d = 1;
	printf("%d %d %d %d", a, b, c, d);
	*/

	int a = 1;
	printf("++a : %d \n", ++a); //2
	a = 1;
	printf("a++ : %d\n", a++); //1
	printf("a : %d\n", a);	   //2
	return 0;
}