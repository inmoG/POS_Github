```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width" />
    <title>웹 페이지 제목</title>
  </head>
  <body>
    <h1>Hello!</h1>
    <ol>
      <li>
        <a
          href="<https://www.opentutorials.org/course/3084>"
          target="_blank"
          title="생활코딩 HTML"
          >HTML</a
        >
      </li>
      <li>CSS</li>
      <li>JavaScript</li>
    </ol>
    <button>Click!</button>
  </body>
</html>
```

&lt;!doctype html html&gt; 파일이 시작된다는 관용적 표현이다.

&lt;html&gt; 모든 태그의 최상위 태그다. 따라서 html 문서의 모든태그를 포함해야한다.

&lt;head&gt; css link, incoding 등 html 문서를 설명하는 태그들을 포함한다.

&lt;body&gt; 본문의 태그 즉 화면에 출력되는 태그를 포함한다.

&lt;a&gt; 태그는 anchor 태그이며 하이퍼 링크를 가지고 있다.
그리고 새로운 페이지를 링크로 연결시켜준다.

information 정보 즉 브라우저에게 알려줄 정보는 head 파트.

Contents 작성할 내용 즉 사용자에게 보여줄 정보는 body 파트

JavaScript code는 &lt;script&gt; 태그에서 쓰여진다.

# HTML

**HTML :** 웹 페이지를 구성하는 가장 중요한 언어.
**<Tag> :** **tag**는 **<start tag>**, **</end tag>**로 구성된다.
**<HTML>** this is HTML tag **</HTML>**

<p></p> 는 단락을 구분한다.
<strong></strong> 는 강조를 의미한다.
<br/> 는 줄바꿈을 의미한다.
< 는 HTML 특수문자로 `&lt;`이다.
> 는 HTML 특수문자로 `&gt;`이다
공백은 HTML 특수문자로 `&nbsp;`이다.

# WEB

웹은 퍼블릭 도메인(Public Domain)입니다.
공공재 즉 누구나 사용할 수 있습니다.
그리고 누구나 접근할 수 있습니다.

웹의 핵심적인 철학은 접근성입니다. 웹은 모든 운영체제에서 동작하고,
웹페이지의 소스코드는 누구나 볼 수 있고, 웹은 저작권이 없는 순수한 공공재입니다.
웹의 이런 특징들이 웹을 다른 기술들과 구별되는 특별한 것으로 만든다고 생각합니다.
거기에 더해서 누구나 차별없이 정보에 접근할 수 있어야 한다는 철학을 접근성(accessibility)라고 합니다.

특히 웹이 중요하게 생각하는 접근성은 신체적인 장애가 있는 사람도 웹을 통해서 정보에 접근할 수 있어야 한다는 것입니다.

예를 들어서
시각장애가 있는 사람은
스크린리더(screen reader)와 같은 프로그램을 이용해서
정보를 청각화해서 접하게 됩니다.

그런데
웹페이지를 예쁘게 하기 위해서
HTML을 사용하지 않고
웹페이지 전체를 이미지로 만든다면
시각 장애가 있는 분들에게는
암흑과도 같은 상태가 됩니다.

자신도 모르는 사이에 누군가를 소외시키고 있는 것입니다.
HTML을 의미론적으로 잘 사용한다면 자신도 모르는 사이에 누군가에게 정말 큰 도움을 주고 있는 것입니다.
이렇게 HTML은 비즈니스적인 측면에서도 중요하지만, 휴머니즘적인 측면에서도 중요한 기술입니다.

---

# img 태그

```
<img src="" width="">

```

`src` 와 `width` 는 태그의 속성이다. 속성은 태그만으론 설명이 부족해 태그의 내용을 보충해주기 위해 사용된다.

# 부모와 자식태그

```html
<ul>
  <li>치킨</li>
  <li>피자</li>
  <li>떡볶이</li>
</ul>
```

<ul> 태그는 <li> 태그의 부모다.
<li> 태그는 <ul> 태그의 자식이다. 또한 항상 함께 쓰인다.
이렇게 함께 쓰이는 태그를 부모 자식태그라 한다.
<ol> : ordered list
<ui> : unordered list

<ol>태그는 **1. 2. 3.** 같은 순서를 자동으로 표시해준다.

## table, td, tr 태그

```
<table>
  <tr>
    <td>head</td>
    <td>98.1</td>
  </tr>
  <tr>
    <td>body</td>
    <td>97.9%</td>
  </tr>
</table>


```

<table>, <td>, <tr> 한 묶음이다.
<td> 태그는 열을 의미한다.
<tr> 태그는 행을 의미한다.

# meta Tag

meta tag : 추가정보를 담는 태그

```
<head>
  <meta charset="utf-8">
  <link rel="stylesheet" href="index.css"/>
</head>
<body>
  <h1>this is 생활코딩 Web1 course</h1>
  <script src="index.js">JavaScript code</script>
</body>

```

```
<meta charset='utf-8'> // 인코딩 방식을 표현한다.
<meta name='author' content='Nomad Coders'>
<meta name='description' content='welcome to my page'> // 페이지를 소개한다.

```

# id 와 class Tag

여러개의 동일한 태그를 구분짓는 방법이 필요하다.
ID는 고유한 엘리먼트를 선언할 때 사용한다.
class는 반복해서 사용할 수 있어 여러 개를 사용한다.

여권번호 : ID
국적 : class

ID > Class > tag
