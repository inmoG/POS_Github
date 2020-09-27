# CSS

css는 2가지 파트로 구성된다.

- selector : h1, div Tag
- property : property-name : value;

## css 문법

- 태그

  ```css
  h1 {
    property-name: value;
    property-name: value;
  }
  ```

- id

  ```css
  #h1 {
    property-name: value;
    property-name: value;
  }
  ```

- class

  ```css
  .h1 {
    property-name: value;
    property-name: value;
  }
  ```

- 태그와 class

  ```css
  h1 .name {
    property-name: value;
    property-name: value;
  }
  ```

css는 "css" 확장자를 사용한다.
css를 별도의 파일로 관리하려면 아래와 같이 작성한다.

```html
<head>
  <link href="styles.css" rel="stylesheet" />
</head>
```

엘리먼트는 박스다. 4개 요소 `contents`, `padding`, `border`, `margin`로 구성된다.

1. margin : 박스의 `border`에서 바깥쪽으로 있는 간격
2. border : 박스의 경계선
3. padding : 박스의 `border`에서 안쪽으로 있는 간격
4. contents : 내용
