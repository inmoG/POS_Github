# Postion property

## fixed

1. static
   `default` 값이다. 그래서 `position`을 지정하지않으면 `static` 값이 적용된다.
   `element`가 다른 태그와의 관계에 의해 자동으로 배치되며 위치를 임의로 설정한다. 그래서 스크롤을 내리면 보이지 않는다.
   지정된 위치에 고정되어 있어 상하좌우 값을 지정할 수 없다.
   부모 요소 내에 자식 요소로서 존재할 때는 부모 요소의 위치를 기준으로 배치된다.

2. fixed
   `element`가 스크린의 '뷰포트(viewport)를 기준으로 한 위치'에 배치된다. 따라서 스크롤되어도 움직이지 않는 고정된 자리를 갖게된다.
   상하좌우 값을 지정할 수 있다.

## relative-absoulte

3. absoulte
   `html` 상에서 해당 `element`와 관계 있는(relative-부모박스) `element`를 찾은 뒤 이에 적합한 포지션이 결정된다.
   적합한 부모박스가 없으면 `body Tag`(문서 본문)에 맞춰 설정한 값으로 움직인다.
   하지만 `relative-element`(부모박스)가 있다면 `relative-element`(father element)안에서 적합한 포지션을 설정한다.
   상하좌우 값을 지정할 수 있으며 스크롤을 내리면 보이지 않는다.

4. relative
   absoulte의 부모박스다.
   상하좌우 값을 지정할 수 있으며 스크롤을 내리면 보이지 않는다.
