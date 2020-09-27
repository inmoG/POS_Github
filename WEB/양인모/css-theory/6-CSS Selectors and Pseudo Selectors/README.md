# CSS Selectors and Pseudo Selectors

- Pseudo selectors : 가상 셀렉터를 뜻하며 팀으로 일할 때 자주 사용한다.

```css
input[type="submit"] {
  background-color: red;
}
```

- `id`,`tag`,`class`를 사용하지 못하는 경우 가상셀렉터를 사용할 수 있다.

```css
.box:first-child {
  background-color: red;
}
```

- 여러 박스 중 첫번째 박스만 빨간색을 적용하고 싶을 때 사용한다.
- 마지막 박스는 `last-child`, n번째 박스는 `nth-child(n)`을 사용한다.

```css
input + .box {
  border: 1px solid black;
}
```

- input과 box class는 형제라는 의미다.

```css
.container > .box {
  background-color: indigo;
  border: 1px solid black;
}
```

- direct child라면 indigo색상이 적용된다. 직계가 아니면 적용되지 않는다.

```css
.child {
  background-color: khaki;
}
```

- direct child가 아니여서 indigo색상이 적용되지않는다.

---

<a href='http://www.topdesignagencies.com/nth-test/'>Pseudo selectors</a>
