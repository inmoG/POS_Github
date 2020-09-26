# Inline vs Block vs Inline Block

1. Inline

   - Inline은 아래의 형태를 갖는다.

     `[text] [text] [text]`

   - `element`의 모든 속성 설정값을 지운다.
   - 설정한 `element`의 속성 값이 아닌 작성한 내용의 `width`, `height` 만큼 스타일이 적용된다.
   - inline은 `element`가 아니라 `Text`다.

2. Block

   - 블록은 아래의 형태를 갖는다.
     ```
     [Block]
     [Block]
     [Block]
     ```
   - `width`, `height` 가 적용된다.
   - 블록 옆에 **다른 블록이 올 수 없다**.
   - `element` 크기와 상관없이 옆에 **다른 element가 위치하는 것을 허용하지 않음**

3. Inline Block

   - `Inline Block` 은 아래의 형태를 갖는다.

     `[Block] [Block] [Block]`

   - `width`, `height`가 적용된다.
   - 블록 옆에 **블록이 존재**한다. 여러 블록이 한 라인에 생성될 수 있음
   - `inline` 과 `block`을 동시에 쓰고 싶다면 사용한다.

---

## 3줄 요약

1. `element`의 폭, 높이만큼 스타일이 적용되면 좋겠다? >> Inline
2. 라인에 블록 한 개씩 사용하고 싶다? >> Block
3. 라인에 블록을 여러 개 사용하고 싶다? >> Inline Block
