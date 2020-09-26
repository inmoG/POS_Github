- GIT : 파일 변경사항 추적 시스템
  _# 파일의 히스토리를 보여준다. 무엇을 몇시에 누가했는지 등등_
- Repository : 소스코드를 저장하는 폴더, `GIT`은 `Repository` 폴더를 추적한다.
- Commit : 파일변경 기록내역. `GIT`은 `Repository` 파일 변경 내역을 `Commit`하여 기록한다. _# 코드가 변경되었다면 `Commit`을 확인해 변경 내역을 알 수 있음_
- Master Branch : `default branch`로서 모든 `commit`이 반영된다. 마지막 작업
  결과물 즉 완성본 Branch다.
- branch : `Master Branch`의 복사버전으로 추가할 코드를 `branch`에 작성한다.
  코드를 테스트해 새로운 기능이 완성되면 `branch`를 `Master Branch`에 합쳐 유저들에게 기능을 공개한다. - master branch : 메인 코드 - new branch : 추가 코드
- push : `Commit`을 해도 `Github`에 **업로드** 되는 것은 아니다. `Local Repository`인 내 컴퓨터에서 `Lomote Repositiory`인 `Github`에 `push`를 해야 업로드가 된다.

- Github : 코드 변경사항을 Github에 업로드 하는 클라우드 웹사이트.
  `Commit` 내역과 변경된 파일 내용을 확인할 수 있다. 코드를 공개할 수 있으며
  언제든지 다운 받을 수 있다.

- git init : 레포지토리 생성
- .git : 깃 레포지토리
- git status : 깃 상태 확인
- git add : 스테이징 단계로 파일 추가
- git commit : 버전 생성
- git log : 버전 확인
- git log --stat : commit file status 확인
- git remote add origin(별명) remote repo : 원격 저장소 연결
- git remote -v : 원격 저장소 주소 확인
- git push : 버전 업로드
- git clone remote repo : 원격 저장소 복제
- git restore --staged <file path> : 스테이징 단계에서 이전으로 되돌린다.
