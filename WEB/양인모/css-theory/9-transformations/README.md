# Transformations

- Html Element 모습을 변형시킨다.
- state, transitions 속성을 함께 사용할 수 있다.

```css
.box {
  width: 300px;
  height: 300px;
  background-color: brown;
  transition: 5s ease-in-out;
  /*5초 동안 ease-in-out 속성이 실행된다.*/
}

.box:hover {
  /*hover state가 발생하면 transform 속성이 실행된다.*/
  transform: rotate(1turn);
}
```

---

<a href='https://developer.mozilla.org/en-US/docs/Web/CSS/transform'>transform MDN</a>
