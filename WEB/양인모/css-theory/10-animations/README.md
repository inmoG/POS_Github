# Animations

- `transform`, `transitions` 효과를 계속 사용하고 싶을 때 사용한다.
- `@keyframe Animations-Name{ from{} to{} }`을 선언하면 사용할 수 있다.

```css
.box {
  width: 300px;
  height: 300px;
  background-color: cadetblue;
  animation: 1.5s scaleAndRotateSquare ease-in-out;
}
@keyframes scaleAndRotateSquare {
  from {
    transform: none;
  }
  to {
    transform: rotate(1turn) scale(0.5, 0.5);
  }
}
```

- 만약 변화되는 상태에 따라 `Animations`을 적용하고 싶다면 아래와 같이 사용한다.

```css
@keyframes scaleAndRotateSquare {
  0% {
    transform: none;
  }

  30% {
    transform: rotate(2turn);
    background-color: darkmagenta;
  }

  70% {
    transform: scale(0.5, 0.5);
    background-color: dodgerblue;
  }

  100% {
    transform: none;
  }
}
```
