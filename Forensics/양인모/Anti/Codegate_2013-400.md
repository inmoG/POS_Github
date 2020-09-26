# 문제

Find key(docx)

Hint 1 : docx 파일을 비교하시오.
Hint 2 : Extra_Field_Entry

---

제공된 파일은 docx 파일이다. 파일을 열면 아래와 같이 몇 장의 사진이 있다.

![codegateF300.png](https://images.velog.io/post-images/jjewqm/d81fa740-0cd2-11ea-a434-7da614d582c7/codegateF300.png)

![codegateF300-2.png](https://images.velog.io/post-images/jjewqm/da781630-0cd2-11ea-a434-7da614d582c7/codegateF300-2.png)

![codegateF300-3.png](https://images.velog.io/post-images/jjewqm/dca49320-0cd2-11ea-93e9-b30c5bc0bd99/codegateF300-3.png)

특별한 건 없어보인다. 정확한 분석을 위해 Hex Editor로 파일을 확인하겠다.

![codegateF300-4.png](https://images.velog.io/post-images/jjewqm/38c55270-0cd3-11ea-afc1-59bb2372aade/codegateF300-4.png)

확인결과 파일은 PK 시그니처를 사용한다.
**docx** 확장자는 이진복합파일로서 PK 시그니처를 사용하며 확장자를 **zip**으로 변경하면
데이터를 은닉할 수 있다.
해당 파일 역시 이진복합파일 구조를 악용해 데이터를 은닉했을 가능성이 있다.
zip 파일로 변경해 은닉된 데이터를 찾아보겠다.

![codegateF300-5.png](https://images.velog.io/post-images/jjewqm/171f51b0-0cd4-11ea-afc1-59bb2372aade/codegateF300-5.png)

**zip**으로 변경 후 파일을 열면 rels, docProps, word, [Content_Types].xml 파일을 볼 수 있다.
압축을 풀어 **document.xml.rels** 파일을 확인하겠다.
**document.xml.rels**는 ID와 각 데이터의 연결정보를 확인할 수 있는 파일이다.

_# document.xml.rels 경로 : \word\\\_rels\document.xml.rels_

![codegateF300-6.png](https://images.velog.io/post-images/jjewqm/2b926310-0cd6-11ea-93e9-b30c5bc0bd99/codegateF300-6.png)

**media** 폴더는 문서파일의 이미지 파일들이 존재하는 폴더다.
파일들이 **document.xml.rels**에 연결되어 있지만 **image6.emf** 파일만 연결되어 있지 않다.

\_media 경로 : # \word\media\_

![codegateF300-7.png](https://images.velog.io/post-images/jjewqm/9c6d87e0-0cd6-11ea-93e9-b30c5bc0bd99/codegateF300-7.png)

해당 파일을 열면 지원되지 않는 포맷이라 읽을 수 없다.
**document.xml.rels**과 연결되어 있지 않고 열리지도 않는다.

![codegateF300-8.png](https://images.velog.io/post-images/jjewqm/04b2b320-0cdc-11ea-91bb-276b6afbf655/codegateF300-8.png)

그럼 **image6.emf**는 왜 media 폴더에 있는걸까?
**image6.emf**에 데이터가 은닉 되어 있는 것 같아 해당 파일을 분석하겠다.

![codegateF300-9.png](https://images.velog.io/post-images/jjewqm/57e67c10-0cdd-11ea-91bb-276b6afbf655/codegateF300-9.png)

hex editor로 확인하니 **[ 50 4B 03 04 14 00 06 00 ]**시그니처가 있다.
이 시그니처는 **docx, pptx, xlsx** 시그니처다.
**docx** 파일로 변환해 열어보겠다. 변환한 파일을 열었더니 **2013** 숫자가 존재한다.  
![codegateF300-10.png](https://images.velog.io/post-images/jjewqm/c05df430-0cdd-11ea-a1a2-5dcf0d7879db/codegateF300-10.png)

**2013**이 KEY인 줄 알았지만 KEY가 아니다.
![codegateF300-11.png](https://images.velog.io/post-images/jjewqm/fe7eccd0-0cdd-11ea-a1a2-5dcf0d7879db/codegateF300-11.png)

**.docx, .xlsx, .pptx**는 OOXML(Office Open XML) 즉 Office 문서용 XML 기반 형식이다.
해당 파일 구조는 파일이름 뒤에 추가 정보를 저장하는 **Extra Field**가 있다.
구글링 결과 **Extra field**에 데이터를 은닉할 수 있다고 한다.
두번째 힌트가 **Extra_Field_Entry** 인걸로 봐선 이 영역을 분석하면 KEY를 찾을 수 있을 것 같다.

![codegateF300-12.png](https://images.velog.io/post-images/jjewqm/026da0f0-0ce3-11ea-a1a2-5dcf0d7879db/codegateF300-12.png)

_# 빨간색 영역 : File Name_
_# 파란색 영역 : Extra Entry_

Extra Field 영역에 데이터를 은닉, 추출하는 도구인 **OOXML Steganography V4**를 사용하겠다.

## OOXML Steganography V4 분석

![codegateF300-113.png](https://images.velog.io/post-images/jjewqm/e4be0050-0ce6-11ea-9b54-31f394c96976/codegateF300-113.png)

### 결과

![codegateF300-14.png](https://images.velog.io/post-images/jjewqm/f0e4cf80-0ce6-11ea-afe4-a5b085fe125d/codegateF300-14.png)

분석 결과 어떠한 데이터도 추출되지 않았다.
그리고 XOR/AES 기능이 OFF 되어있고 원본의 **-3.03%**가 복구되었다고 한다.
**image6.docx**에서 확인한 **"2013"**이 **AES 복호화 KEY**라 예상된다.
**"2013"** 키를 넣어 다시 분석하겠다.

## OOXML Steganography V4 2차 분석

![codegateF300-15.png](https://images.velog.io/post-images/jjewqm/80a1fda0-0ce7-11ea-9b54-31f394c96976/codegateF300-15.png)

### 결과

![codegateF300-16.png](https://images.velog.io/post-images/jjewqm/871aa330-0ce7-11ea-bd4b-d35c70e3c1ec/codegateF300-16.png)

분석 결과 **c0d2gate~2o13!!F0r2nsic!!!!!** KEY를 얻어냈다.

**KEY : c0d2gate~2o13!!F0r2nsic!!!!!**

---

본 글은 http://www.ctf-d.com/ 를 참고합니다.

**참고자료 :**
http://forensic-proof.com/archives/325
https://yokang90.tistory.com/m/30?category=546889
https://ko.wikipedia.org/wiki/복합_파일_이진_형식
https://www.linux.co.kr/home2/board/subbs/board.php?bo_table=lecture&wr_id=1389
https://blog.naver.com/PostView.nhn?blogId=empty7792&logNo=221508900148&parentCategoryNo=&categoryNo=11&viewDate=&isShowPopularPosts=true&from=search

OOXML Steganography V4 다운로드 링크https://www.mediafire.com/file/m9hk90yv93lhfld/ooXML_Steganography_v4.zip/file
