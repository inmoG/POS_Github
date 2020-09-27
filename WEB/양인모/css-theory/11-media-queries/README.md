# Media Queries

- 브라우저의 크기를 알려주는 속성이다.
- 반응형 웹 디자인을 할 때 사용된다. 예를 들어 사용자가 모바일 환경인지 데스크탑 환경인지 알 수 있다.
- 원하는 css 속성을 `@media screen`에 선언한다.

```css
body {
  background-color: forestgreen;
}

@media screen and (min-width: 320px) and (max-width: 640px) {
  body {
    background-color: yellow;
  }
}
```

---

<a href="https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries">Media Queries MDN</a>
