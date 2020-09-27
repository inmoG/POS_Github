A회사 보안팀은 내부직원 PC의 자체보안감사 중 특정직원 PC에서 인터넷을 통해 **내부문서를 외부로 업로드 한 흔적을 발견하였다.** 보안팀은 보안 위반 흔적을 더 찾기 위해 직원 **스마트폰**도 임의 제출을 받아 추가 흔적을 조사하였다. 내부문서의 정보를 찾아 정답을 입력하시오.

KEY Format : Upload Date&Time(UTC+09:00)\_Modified Date&Time(UTC+09:00)\_FileName.Extention_Filesize(LogicalFileSize)
ex)2013/03/01&21:00:00_2013/04/03&10:00:50_sample.docx_100MB

---

![dropbox.png](https://images.velog.io/post-images/jjewqm/cad87120-0aa7-11ea-829a-cf184fab93de/dropbox.png)

문제파일은 encase 확장자 001 압축파일이다.
FTK imager로 열어보니 알수없는 문자열의 폴더들이 있다.

![dropbox2.png](https://images.velog.io/post-images/jjewqm/09e111b0-0aa8-11ea-8504-b9da56513532/dropbox2.png)

dropbox.app을 사용한 흔적이 있다. dropbox는 클라우드 서비스를 제공하는 어플리케이션으로 내부문서를 유출시킬 수 있는 프로그램이다.
해당 경로를 조사한 결과 S-Companysecurity.pdf를 캡쳐한 png파일을 확인했다.

![dropbox3.png](https://images.velog.io/post-images/jjewqm/7561ab20-0aa8-11ea-8504-b9da56513532/dropbox3.png)

dropbox.app을 조사해야할 필요성이 있어 Library\Caches\cache.db 파일을 분석하겠다.
해당 파일은 어플리케이션의 캐시정보를 지닌 파일로 Dropbox 앱이 동기화 할 때, 동기화 된 정보가 남는 파일이다.
cache.db 파일을 FTK Imgaer의 Export Files 기능으로 추출하겠다. cache.db 파일은 SQLite format을 사용하므로 DB Browser for SQLite로 분석하겠다.

## cache.db 분석결과

![dropbox4.png](https://images.velog.io/post-images/jjewqm/53f08b20-0aab-11ea-983a-4fa2708ad07c/dropbox4.png)

cahce.db의 데이터 파일들은 plist파일 형식을 사용한다. plist 즉 프로퍼티 리스트(property list)는 OS X, iOS, NeXTSTEP, GNUstep 프로그래밍 소프트웨어 프레임워크 등에 이용되는 객체 직렬화를 위한 파일이다. 또한 .plist라는 확장자를 가지므로, 보통 plist 파일이라고 하는 경우가 많다. 데이터 내용을 보니 base64로 인코딩 되어있다. plist editor pro 윈도우 버전으로 plist 파일을 분석하겠다.

## plist 분석결과

![plist.png](https://images.velog.io/post-images/jjewqm/024a9150-0aae-11ea-b115-e7d3c89858d0/plist.png)
xml view에 데이터를 붙여넣기 후 list view로 결과를 확인하면 된다.
S-Companysecurity.pdf 파일을 검색해 **두 개의 NS.time**과 **2.1 MB 파일크기**를 확인했다.
![plist결과.png](https://images.velog.io/post-images/jjewqm/11888b90-0aae-11ea-b115-e7d3c89858d0/plist결과.png)

## dropbox.sqlite 분석

시간정보에 대한 추가 정보를 위해**5BB3AF5D-01CC-45D9-947D-988DB30DD439\Documents\dropox.sqlite**를 분석하겠다.

![dropbox6.png](https://images.velog.io/post-images/jjewqm/ec939c30-0ad5-11ea-ad15-c7e1124c7bfc/dropbox6.png)

ZCACHEDFILE 테이블은 업로드할 때 생성된 캐시가 모인 데이터를 가진다.

## 결론

plist의 첫번째 NS.time과 ZCACHEDFILE의 ZMODIFIEDDATE 시간이 동일해 첫번째 NS.time은 업로드 시간임을 알 수 있다. 2번 NS.time 시간은 업로드 시간 이전이므로 수정시간이라 유추할 수 있다.

_# 아이폰이기 때문에 **Decode Format : MAC: Absolute Time** 으로 설정한다._

### 1번 NS.time

![dropbox7.png](https://images.velog.io/post-images/jjewqm/d076e280-0ad7-11ea-ae22-bfee9d5b12d8/dropbox7.png)

### 2번 NS.time

![dropbox8.png](https://images.velog.io/post-images/jjewqm/d2c0f990-0ad7-11ea-ae22-bfee9d5b12d8/dropbox8.png)

---

**정답 : 2012/12/27&17:55:54_2012/05/01&17:46:38_S-Companysecurity.pdf_2.1MB**
