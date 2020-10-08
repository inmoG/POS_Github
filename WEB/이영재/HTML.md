# __HTML__<br/>
## HTML이란?
- Hyper Text Markup Language의 약어로 (웹페이지에서 다른 페이지로 이동할 수 있도록하는 것) 기능을 가진 문서를 만드는 언어이다.
다시말해, 구조를 설계할 때 사용되는 언어로 hyper link 시스템을 가지고 있으며, 흔히 말하는 웹페이지를 위한 마크업 언어이다.<br/>
  - 장점: 다른 언어보다 쉬우며, 중요하다. public domain이다.
  - 단점: 내용의 의미보다는 내용을 외양적으로 표현하는 태그에 치중되어 있다.
<br/><br/>
- 기본구조<br/>
```html
<!DOCTYPE>
<html>
<head>
    <title>제목</title>
    <meta charset ='utf-8' />
<head>
<body>
    <h1>Helo</h1>
    <div>
      <p>Welcome to HTML World!</p>
      <img src = "https://s3-ap-northeast-2.amazonaws.com/opentutorials-user-file/course/1/5641.png">
    <div>
</body>
</html>

```
DOCTYPE : 파일이 시작된다는 관용적 표현<br/>
html : 전체 html 문서를 감싸는 태그<br/>
head : html 문서에 대한 정보를 나타내는 부분<br/>
body : html 문서에서 실제적으로 보여지는 부분<br/>
title : head안에 들어가는 태그로 제목 표시줄의 내용을 나타냄<br/>
meta : 문서에 대한 설명을 표시<br/> 
h1 : body 안에서 제목을 표시하는 태그, 중요도에 따라 h1 ~ h6까지 있음<br/>
div : 구역을 표시하는 태그<br/>
p : 문단을 표시하는 태그<br/>
img : 이미지를 표시하는 태그<br/>
```
<img src="" width="">
```
<br/>

## __부모자식과 목록__
```
<p> #parameter: 문단 <- 부모
    <a href="https"=github.com">github</a> <- 자식
<p>
```
```html
<ul> #unordered list
    <li/>영재</li>
    <li/>동우</li>
</ul> 

```

## __table, td, tr__
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
> `<table>, <td>, <tr>` 같이 사용<br/>
`<td>` 태그는 열을 의미<br/>
`<tr>` 태그는 행을 의미

<br>

## __Meta Tag__
`<meta>` : 문서정보를 담고 있는 태그
```html
example)

<meta charset='utf-8'/>
<meta name="title" content ="이 문서의 제목은 000 입니다."/>
```
