# Transitions

- Elements에 css를 동적으로 주는 효과
- css state 발생 시 애니메이션 효과를 준다.
- state는 `hover`, `active`, `focus`, `visited`가 있으며 `hover`, `actiove`, `focus`만 `Transitions` 효과가 적용된다.
- 아래 코드를 실행하면 `background-color`와 `color`가 파랑색과 빨간색으로 변한다.

```css
.box {
  background-color: green;
  color: white;
  transition: background-color, color 5s ease-in-out;
  /*모든 css 속성을 변경하고 싶으면 `all` 을 사용한다.*/
}

.box:hover {
  background-color: blue;
  color: red;
}
```

---

<a href="https://developer.mozilla.org/en-US/docs/Web/CSS/transition">transition MDN</a>
