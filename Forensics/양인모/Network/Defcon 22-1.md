# 문제

사건을 수락해 주셔서 감사합니다. 우리의 러시아 동지는 스노든이 발표 한 문서에서 2015 체스 복싱 세계 타이틀과 관련된 뇌물에 관한 정보가 포함되어있을 것이라고 밝혔다. 우리는 스노든의 트래픽을 감시해 왔고, 관련된 모든 사람을 알아야합니다. 사용자 이름 목록이 있는 것으로 의심되며, 목록의 두 번째 이름이 누구인지 알고 싶습니다. 이 폴더에 있는 Round1 패킷 캡처를 사용하여 사례에 대해 자세히 알아보고 다음 질문에 답하십시오. **사용자 이름 목록에서 두 번째 이름은 무엇입니까?**

Hint : 너의 모든 base64는 우리에게 속해있다.

---

![Defcon 22 #1.png](https://images.velog.io/post-images/jjewqm/01aa9e30-0b66-11ea-a993-5ffc98f352d3/Defcon-22-1.png)

패킷의 수는 30775개다. 패킷을 훑어보니 SMB프로토콜로 파일을 송수신한 흔적이 있다.

_SMB 프로토콜 : Server Message Block.
SMB는 네트워크 상 존재하는 노드들 간에 자원을 공유할 수 있도록 설계된 프로토콜이다. 주로 네트워크에 연결된 컴퓨터끼리 파일, 프린터, 포트 또는 기타 메시지를 전달하는데 사용된다_

![Defcon 22 #1-2.png](https://images.velog.io/post-images/jjewqm/a12c2e40-0b5e-11ea-a993-5ffc98f352d3/Defcon-22-1-2.png)

SMB 프로토콜 패킷을 추출하기 위해 File - Export Objects - SMB 선택한다.

![Defcon 22 #1-5.png](https://images.velog.io/post-images/jjewqm/3bc3ea90-0b61-11ea-8b6a-31085950b69b/Defcon-22-1-5.png)

그리고 문제에선 **트래픽에 사용자 이름 목록이 있는 것으로 의심한다** 하였다.
문서파일에 이름 목록이 있을 가능성이 높으니 Documents.zip 파일을 저장하겠다.

![Defcon 22 #1-6.png](https://images.velog.io/post-images/jjewqm/25b26410-0b62-11ea-a993-5ffc98f352d3/Defcon-22-1-6.png)

![image.png](https://images.velog.io/post-images/jjewqm/72cd0130-0b92-11ea-bd21-351eb7aee0bc/image.png)

파일은 4개의 폴더와 1개의 압축파일로 이루어지고 각 폴더에는 docx 문서가 있다. docx 문서들은 아래 예시와 같이 base64로 인코딩 되어있다.
![Defcon 22 #1-7.png](https://images.velog.io/post-images/jjewqm/065234a0-0b63-11ea-a8a6-6b4f153fa7de/Defcon-22-1-7.png)

각 docx문서의 base64를 디코딩하겠다.

## Actual Documents\GoT Spoilers.docx

![GoT Spoilers.png](https://images.velog.io/post-images/jjewqm/551c13c0-0b64-11ea-bdb3-2b5e4c739bc0/GoT-Spoilers.png)

### 결과

![GoT Spoilers2.png](https://images.velog.io/post-images/jjewqm/5f3ab6e0-0b64-11ea-bdb3-2b5e4c739bc0/GoT-Spoilers2.png)

## Enter the WuTang\track6.docx

![Enter the WuTang.png](https://images.velog.io/post-images/jjewqm/d3401990-0b64-11ea-a993-5ffc98f352d3/Enter-the-WuTang.png)

### 결과

![Enter the WuTang2.png](https://images.velog.io/post-images/jjewqm/dca22370-0b64-11ea-8436-d760115d3f82/Enter-the-WuTang2.png)

문서들을 계속 디코딩한 결과 사용자 이름 목록으로 의심되는 문건을 찾았다.
해당 문서는 Enter the WuTang\track6.docx 문서이며 목록의 두번째 이름은 **Kim Ill-Song**이다.

### 정답

**Kim Ill-Song**

---

본 글은 http://www.ctf-d.com/challenges 문제를 풀이합니다.
