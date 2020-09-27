# 문제

서울에 위치한 X 에너지 기업이 APT 공격을 받았다. 공격자 A는 6개월 동안 정교한 공격으로 중요한 정보를 훔쳤다. 공격자 A는 공격하는 동안 악성파일, 프리패치, 레지스트리 및 이벤트 로그와 같은 모든 흔적을 제거하기 위해 많은 노력을 기울이므로 X 에너지 기업에서 공격 경로를 찾기가 어려웠다. 하지만 포렌식 전문가인 IU는 MFT를 분석해서 공격자 A의 흔적을 찾을 수 있었다. 주어진 MFT를 분석하여 아래 질문에 답하시오.

---

시간은 한국 표준시 (UTC + 09 : 00) 기준으로 한다.

1. 악성파일의 이름은 무엇인가?
   (abcd.hwp)
2. 악성파일이 생성된 시간은 언제인가?
   (YYYY-MM-DDThh:mm:ss.sssssss)
3. 악성파일의 파일 사이즈는 어떻게 되는가?
   (1234 byte)

## 분석

MFT를 분석해 악성파일 이름을 찾아야 한다. 악성파일은 실행파일(응용프로그램)이다.
실행파일은 hwp,doc,xls,ppt,bat,exe,pdf가 있다.
\$MFT는 MFT엔트리를 관리하는 엔트리이다. MFT엔트리는 23개가 있다.
엔트리 23개를 지나면 데이터를 관리하는 **데이터 영역**이 있다.
빠른 분석을 위해 70섹터를 건너뛰자.
_#엔트리 당 2섹터를 사용해 70섹터를 건너뛴다. 0x23 \* 2 = 70_

![코드케이트400_MFT분석-2.png](https://images.velog.io/post-images/jjewqm/02d09a00-09d9-11ea-ab33-0979f6b714dc/코드케이트400MFT분석-2.png)

70섹터부터 데이터들이 존재하지만 섹터 하나씩 확인해가며 찾는 방식은 시간이 오래걸려 비효율적이다. string.exe 를 사용해 키워드 검색으로 빠르게 분석하겠다.
`string.exe $MFT >> mft.txt`

데이터가 커 sublime Text 툴로 결과를 확인하겠다.
**hwp, doc, xls, ppt, bat, exe, pdf** 검색결과 수상한 **exe 파일**이 검색되었다.
![코드케이트400_MFT분석.png](https://images.velog.io/post-images/jjewqm/20b2f120-09da-11ea-ab33-0979f6b714dc/코드케이트400MFT분석.png)

휴지통은 아래 그림과 같이 SID로 구분해 허가된 사용자만 해당 휴지통에 접근할 수 있다.

![휴지통.png](https://images.velog.io/post-images/jjewqm/cb1edf20-09da-11ea-90c1-e5ad54d8c976/휴지통.png)

하지만 분석결과 권한 표시가 없어 **강제로 파일을 삭제했다**고 의심할 수 있다. **analyzeMFT**를 사용해 \$MFT의 파일 생성,삭제 흔적을 분석하겠다.
`analyzeMFT.exe -f $MFT -c mft.csv` p.exe 검색했지만 파일이 없다 문자열이 짤린 것 같다.

![코드케이트400_MFT분석1.png](https://images.velog.io/post-images/jjewqm/935b22e0-09dc-11ea-8684-85e742864045/코드케이트400MFT분석1.png)

$Recycle.Bin(휴지통)경로를 검색 결과 __r32.exe__ 실행파일이 있다. cc.dat는 실행파일이 아니므로 r32.exe가 악성파일이다. 해당 파일이 $MFT에 검색되는 건 파일시스템에 존재한다는 의미다. \$MFT에서 해당파일 크기를 확인하겠다.

![코드케이트400_MFT분석-3.png](https://images.velog.io/post-images/jjewqm/0655f360-09dd-11ea-90c1-e5ad54d8c976/코드케이트400MFT분석-3.png)

Decoded text칸에 r32.exe 문자열을 입력해 hex값을 확인해야 한다.
여기서 중요한 건 문자열 공백이다. HxD 에디터로 분석해보면 프로그램이름 사이에 공백(00)이 있는 걸 본 적 있을 것이다. 그래서 **공백**을 입력해 hex값을 구해야 한다.
_#공백은 **문자열 00** 이 아니라 **hex값 00**을 뜻한다._

hex 값 `72 00 33 00 32 00 2E 00 65 00 78 00 65`을 검색해 r32.exe를 찾아야 한다.

## 확인결과

![코드케이트400_MFT분석-4.png](https://images.velog.io/post-images/jjewqm/bf0045f0-09dd-11ea-bfa9-e77f10ad23ad/코드케이트400MFT분석-4.png)

![코드케이트400_MFT분석5.png](https://images.velog.io/post-images/jjewqm/c3425c70-09dd-11ea-8684-85e742864045/코드케이트400MFT분석5.png)

115섹터와 2094섹터에 r32.exe가 존재하며 2094섹터는 r32.exe의 MFT 엔트리다.

## DATA 속성

![$DATA.png](https://images.velog.io/post-images/jjewqm/a782fa70-09de-11ea-8684-85e742864045/DATA.png)

$DATA 속성(80)의 초기화된 크기 오프셋이 파일 사이즈다.
$DATA 속성을 분석해 파일 사이즈 값을 확인하겠다.

![코드케이트400_MFT분석7.png](https://images.velog.io/post-images/jjewqm/8bca0110-09df-11ea-a0a9-85c724cf39b1/코드케이트400MFT분석7.png)

`00 44 01 00 00 00 00 00 >> 82944 Bytes`
10진수로 변환 결과 82944 Bytes가 r32.exe 파일 사이즈다.

![코드케이트400_MFT분석9.png](https://images.velog.io/post-images/jjewqm/e8fae5f0-09e1-11ea-a0a9-85c724cf39b1/코드케이트400MFT분석9.png)

그리고 \$MFT는 파일 생성시간을 기록하며 해당 오프셋이 생성시간 오프셋이다.
오프셋 분석결과 2012년 2월 23일 02:39:18초에 악성파일이 생성되었다.

![코드케이트400_MFT분석10.png](https://images.velog.io/post-images/jjewqm/0dbed310-09e2-11ea-8684-85e742864045/코드케이트400MFT분석10.png)

1. 악성파일의 이름은 무엇인가? **r32.exe**
2. 악성파일이 생성된 시간은 언제인가? **2012-02-22|17:39:18.897461**
3. 악성파일의 파일 사이즈는 어떻게 되는가? **82994 Bytes**

---

생성시간의 ss.sssssss 단위까지 확인 하려면 `analyzeMFT.exe -c` 옵션을 사용해 r32.exe 생성시간을 확인하면 된다. 본 글에선 이해를 돕기위해 MFT 엔트리의 생성시간을 사용한다.
