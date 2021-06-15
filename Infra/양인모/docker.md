## 1 개요

### 1.1 프로젝트 주제

NGINX 도커 환경 구축 및 로그, 이미지 관리

### 1.2 프로젝트 추진 배경 및 목표

최근 개발 환경에서 도커는 필수로 사용되어 도커 환경에서 모의해킹과 침해사고 분석 능력이 요구된다. 따라서 도커 이해와 사고 분석 시 로그 수집에 필요한 기초지식을 목표로 한다.

### 1.3 프로젝트 요약

도커 이해와 환경 구축 및 로그, 이미지 관리

## 2 도커 (Docker)

![](https://images.velog.io/images/jjewqm/post/9d9d2059-fa89-497a-b725-ae9ca617bfe7/image.png)

도커는 2013년에 등장한 컨테이너 기반 오픈소스 가상화 플랫폼이다. 도커는 리눅스 상에서 컨테이너 방식으로 프로세스를 격리해서 실행하고 관리한다. 화물 운송에 사용되는 컨테이너와 도커 컨테이너는 비슷한 개념이다. 다양한 프로그램, 실행환경을 컨테이너로 추상화하고 동일한 인터페이스를 제공하여 프로그램 배포와 관리를 단순화한다. 백엔드 프로그램, 데이터베이스 서버, 등 어떤 프로그램도 컨테이너로 추상화할 수 있고 PC, AWS, Azure, Google cloud등 어디에서나 실행 가능하다. 컨테이너는 격리된 공간에서 프로세스가 동작하는 기술이다. 가상화 기술의 하나지만 기존방식과 다르다. 기존 가상화 방식은 OS를 가상화 하였다. VMware나 VirtualBox같은 가상머신은 호스트 OS위에 게스트 OS 전체를 가상화해 사용한다. 이 방식은 여러 OS를 가상화 할 수 있지만 무겁고 느려 운영환경에선 사용할 수 없었다. 이러한 상황을 개선하고자 CPU 가상화 기술의 KVM과 반가상화의 Xen이 등장하였다. 하지만 여전히 성능문제가 있어 프로세스를 격리하는 방식이 등장하였다.

### 2.1 컨테이너

리눅스에서는 이 방식을 리눅스 컨테이너라고 하고 단순히 프로세스를 격리시키기 때문에 가볍고 빠르게 동작한다. CPU나 메모리는 딱 프로세스가 필요한 만큼만 추가로 사용하고 성능적으로도 거의 손실이 없다. 실행중인 컨테이너에 접속하면 명령어를 입력할 수 있고 apt-get이나 yum으로 패키지를 설치할 수 있으며 사용자도 추가하고 여러 개 프로세스를 백그라운드로 실행할 수 있다. CPU나 메모리 사용량을 제한할 수 있고 호스트 특정 포트와 연결하거나 호스트 특정 디렉토리를 내부 디렉토리인 것처럼 사용할 수 있다. 심지어 컨테이너를 만드는 시간은 1-2초로 매우 빠르다. 컨테이너 개념은 도커가 처음 만든 것이 아니다. 도커 이전에 프로세스 격리 방법으로 리눅스에서는 control groups와 namespace를 이용한 Linux container가 있었고 FreeBSD에선 Jail, Solaris에서는 Solaris Zones이라는 기술이 있었다. 도커는 Linux container를 기반으로 0.9버전에서는 자체적인 libcontainer기술을 사용했고 현재는 runC기술에 합쳐졌다.

![](https://images.velog.io/images/jjewqm/post/016411a7-a17c-4aeb-93ce-24d29c2d7b26/image.png)

### 2.2 이미지

![](https://images.velog.io/images/jjewqm/post/a9dc7cc8-597b-4d1b-9890-12c89d2ec9ec/image.png)

도커는 컨테이너와 이미지로 이뤄진다. 이미지는 컨테이너 실행에 필요한 파일과 설정 값 등을 포함하고 있는 것으로 추가되거나 변하는 값을 가지지 않아 변하지 않는다. 컨테이너는 이미지를 실행한 상태이며 추가되거나 변하는 값은 컨테이너에 저장한다. 같은 이미지에서 여러 개 컨테이너를 생성할 수 있고 컨테이너 상태가 바뀌거나 컨테이너가 삭제되더라도 이미지는 변하지 않고 그대로 남아있다. ubuntu이미지는 ubuntu실행에 필요한 모든 파일을 가지며 gitlab이미지는 centos를 기반으로 ruby, go, database, redis, gitlab source, nginx등을 갖는다. 이미지는 컨테이너 실행에 필요한 모든 정보를 가지고 있어 의존성 파일을 컴파일하고 이것저것 설치할 필요가 없다. 서버에 만들어 놓은 이미지를 다운받고 컨테이너만 생성하면 수십, 수백 대 서버도 운영하는데 문제없다.

### 2.3 레이어 저장방식

![](https://images.velog.io/images/jjewqm/post/bb886fc8-fadc-425f-a193-b07a58674efa/image.png)

도커 이미지는 컨테이너를 실행하기 위한 모든 정보를 가지고 있어 보통 용량이 수백 메가바이트에 이른다. 처음 이미지를 다운받을 땐 크게 부담이 안되지만 기존 이미지에 파일 하나 추가했다고 수백 메가바이트를 다시 다운받는다면 매우 비효율적이다. 도커는 이런 문제를 해결하고자 레이어 개념을 사용하고 유니온 파일 시스템을 이용해 여러 개 레이어를 하나의 파일시스템으로 사용한다. 이미지는 여러 개 읽기 전용 레이어로 구성되고 파일이 추가되거나 수정되면 새로운 레이어가 생긴다. ubuntu 이미지가 A + B + C의 집합이라면, ubuntu 이미지를 베이스로 만든 nginx 이미지는 A + B + C + nginx가 된다. webapp 이미지를 nginx 이미지 기반으로 만들었다면 A + B + C + nginx + source 레이어로 구성된다. webapp 소스를 수정하면 A, B, C, nginx 레이어를 제외한 새로운 source(v2) 레이어만 다운받아 효율적으로 이미지를 관리할 수 있다. 컨테이너를 생성할 때도 레이어 방식을 사용한다. 기존 이미지 레이어 위에 읽기/쓰기 레이어를 추가한다. 이미지 레이어를 그대로 사용하면서 컨테이너가 실행 중에 생성하는 파일이나 변경된 내용은 읽기/쓰기 레이어에 저장해 여러 컨테이너를 생성해도 최소한의 용량만 사용한다.

### 2.4 도커 운영의 장점

A 회사는 B 서버를 1년 전에 구성했고 C 서버는 이제 막 구성했다면 설치 패키지, OS 등 완벽하게 같을 순 없다. 이러한 차이점들이 장애를 일으키고 원인해결에 긴 시간이 걸린다. 이런 상황을 해결하고자 서버를 코드로 구성하고 관리하는 다양한 도구인 Vagrant, Chef, Ansible, Docker가 나타났다.

![](https://images.velog.io/images/jjewqm/post/56e2f400-d06f-4cce-8594-7c71a7460eda/image.png)

도커 파일로 이미지를 만들면 서버가 구성되는 시점이 이미지를 만든 시점으로 고정된다. 이 이미지를 사용해 컨테이너를 배포하면 1년 전 배포한 서버와 오늘 배포한 서버에 설치된 시점이 같다. 이렇듯 도커는 운영환경, 설치 시점에 상관없이 동일한 애플리케이션 환경을 구성할 수 있다.

### 2.5 정보보호팀과 도커

최근 개발 환경에서 도커는 필수로 사용되어 도커 환경에서 모의 해킹과 침해사고 분석 능력이 요구된다. 2.5 절에서는 도커 환경 공격사례를 살펴보며 도커 환경에서 얼마나 많은 공격이 발생하는지 알아본다. **20년7월16일 보안뉴스** 기사에 따르면 기존 공격은 도커 허브에서 이미지를 공략해 컨테이너 호스트까지 침투해 들어갔으나 지금은 자신들만의 악성 이미지를 생성해 호스팅함으로써 보안 관리자들이 악성 이미지를 분별하기 힘들다고 한다. **20년 8월 31일 보안뉴스** 기사에 따르면 잘못 설정된 도커 API 포트를 자동화 도구로 스캔한다. 찾아낸 포트를 통해 공격자 컨테이너를 설정하고 멀웨어를 배포한다. 도커 허브에 공개된 이미지가 악성은 아니지만 취약한 API를 통해 자유롭게 접근이 가능하여 공격 통로가 된다. 결국 도커는 개발 환경에서 필수로 사용되는 만큼 공격자에게 많이 노출되어 있다. 정보보호팀은 도커 환경을 충분히 이해하여야 취약한 포트가 노출되어 있는지, 관리자가 모르는 컨테이너가 섞여 있는지 점검하고 도커 환경을 대상으로 한 모의 해킹과 침해사고 분석 능력을 길러야 한다.

![](https://images.velog.io/images/jjewqm/post/0754935c-f1c9-4fb8-8015-11b77de45259/image.png)

![](https://images.velog.io/images/jjewqm/post/0c09d054-39c5-4b40-9154-6bac99054856/image.png)

## 3 도커 환경 구축

### 3.1 도커 설치하기

![](https://images.velog.io/images/jjewqm/post/4df8dcb4-872b-417f-a0c5-3a83ab0ccae2/image.png)

도커 설치 전 `curl -fsSL https://download.docker.com/linux/debian/gpg | sudo apt-key add -`, `echo 'deb https://download.docker.com/linux/debian stretch stable' > /etc/apt/sources.list.d/docker.list`, `apt-get update` 명령어를 사용해 저장소를 추가하고 패키지를 최신상태로 업데이트한다. 업데이트가 완료되면 `apt-get install docker-ce` 명령어를 사용해 설치한다. 설치가 완료되면 `docker version` 명령어를 입력해 Client와 Server가 정상적으로 출력되는지 확인한다.

![](https://images.velog.io/images/jjewqm/post/f97d739c-5af3-4094-a7bc-be33910c1471/image.png)

### 3.2 도커 이미지 설치하기

`Docker search` 명령어를 사용하거나 `docker hub` 웹 사이트에서 사용할 이미지를 검색한다. 3.2절에서는 nginx를 설치한다.

![](https://images.velog.io/images/jjewqm/post/ab3ae6e4-d6b1-431e-bc3e-fe3e804396d3/image.png)

![](https://images.velog.io/images/jjewqm/post/f99990fa-0c6e-459f-a575-2e384dd2740e/image.png)

`Docker pull` 명령어를 사용해 nginx 도커 이미지를 다운로드한다.

![](https://images.velog.io/images/jjewqm/post/2bfa61a4-ac3e-4721-9231-282420e21c89/image.png)

`Docker images` 명령어를 사용해 정상적으로 다운로드 되었는지 확인한다.

![](https://images.velog.io/images/jjewqm/post/85c00b7a-aee3-483c-b7b0-056c3aa5e412/image.png)

`Docker run` 명령어를 사용해 다운로드 받은 이미지를 컨테이너로 변환한다. 옵션을 사용해 컨테이너 설정을 결정할 수 있다.

![](https://images.velog.io/images/jjewqm/post/bb733638-41fd-4148-8993-a7f3d1944ef3/image.png)

위 처럼 `Docker run -d -p 82:80 nginx` 명령어로 컨테이너를 생성한다. `-p`옵션은 호스트와 컨테이너 포트를 연결하는 옵션으로 외부 호스트에서 81번 포트로 접근해 컨테이너 80번 포트에 접속하는 의미이다. `-d` 옵션은 백그라운드 실행을 의미한다.

### 3.3 Nginx 실행 확인

![](https://images.velog.io/images/jjewqm/post/d90a1f51-322d-42e0-abe4-68274283c91f/image.png)

`localhost:82` 접속 결과 nginx 서버가 작동한다.

## 4 도커 환경 관리

도커를 사용하다 보면 로그가 쌓인다. 로그가 계속 쌓이면 하드디스크 용량 부족사태가 오기 때문에 관리할 필요가 있다. 그리고 로그는 침해사고 대응 시 꼭 수집해야 해 로그 경로를 알아야한다.

## 4.1 도커 환경 로그

도커는 로깅 드라이버로 로그를 생성한다. 로깅 드라이버 기본 타입은 `json-file`로 로그를 json 파일로 저장한다. Docker info 또는 `docker inspect [container name]`명령어를 사용하면 로깅 드라이버 타입을 볼 수 있다.

![](https://images.velog.io/images/jjewqm/post/52918eac-7a7b-4410-a361-5bd463671e20/image.png)

![](https://images.velog.io/images/jjewqm/post/ac95476a-14b5-4c2e-8475-3ef79a094a6a/image.png)

`Inspect` 명령어는 컨테이너와 이미지 세부정보를 JSON 형태로 출력한다. `-f` 옵션을 사용하면 JSON 문서 하위 항목을 지정해 출력한다. 아래와 같이 `{{.HostConfig.LogConfig.Type}}` 항목을 지정하면 로깅 드라이버 정보를 출력한다.

![](https://images.velog.io/images/jjewqm/post/75e9ab68-3252-4fc9-ab24-9d61514a852a/image.png)

로깅 드라이버는 기본 타입 json-file 외에도 syslog, splunk 등 다양한 타입을 지원한다.

![](https://images.velog.io/images/jjewqm/post/e9b7bdc6-63b8-4261-abd6-646a801affb7/image.png)

도커 로그는 `/var/lib/docker/containers/` 경로에 containers 별로 저장한다. 4개 컨테이너가 저장되었으며 컨테이너 ID 앞 4자리 숫자로 컨테이너를 확인할 수 있다.

![](https://images.velog.io/images/jjewqm/post/497138dc-48c5-4706-a40f-abf04d6a3a31/image.png)

Nginx 컨테이너 디렉터리에 json.log 파일 형식으로 로그를 저장한다.

![](https://images.velog.io/images/jjewqm/post/0c89d2a1-9588-47c4-8668-04a03ca8fd2b/image.png)

![](https://images.velog.io/images/jjewqm/post/9770bb3f-51f3-435c-833f-f265020dde44/image.png)

`docker logs [container ID]` 명령어로도 같은 로그를 볼 수 있다.

![](https://images.velog.io/images/jjewqm/post/79173b16-8380-4f74-a08e-a4f1736f2377/image.png)

## 4.2 도커 로그 관리

로그를 주기적으로 관리해야 하드디스크 용량 부족 사태가 발생하지 않는다. 따라서 도커 데몬 설정파일을 수정하거나 `logrotate`로 로그를 관리한다.

### 4.2.1 도커 데몬 설정 파일 변경

`/etc/docker/daemon.json` 파일을 아래와 같이 수정한다. 로그최대 크기는10m, 최대 로그 파일수는 3개로 설정되어 있다.

![](https://images.velog.io/images/jjewqm/post/12ee5c0c-4ab1-4086-991f-d22a9e2feb40/image.png)

### 4.2.2 Logrotate

`/etc/logrotate.d/` 경로에 `Logrotate` 파일을 생성한다. `/var/lib/docker/container/*/*.log`는 로그파일 경로다. `*`를 사용해 디렉터리 내 모든 파일을 관리한다.

![](https://images.velog.io/images/jjewqm/post/55f2415b-c3ad-4d4c-9e4f-1b51409798de/image.png)

## 4.3 컨테이너 내부 접근

도커 컨테이너는 격리된 프로세스 단위로 실행한다. 따라서 컨테이너 내부에 접근해 직접 컨테이너를 관리해야 할 때가 있다. 이 때 `docker exec` 명령어를 사용한다. `Bash` 셸 프로그램이 실행되어 셸 프롬프트가 `root@9afe9318114e:/#`로 변경되었다.

![](https://images.velog.io/images/jjewqm/post/28b70d75-b093-4f80-aeed-95bb19a15a3f/image.png)

컨테이너 내부에 접속한 상태이므로 nginx 서버 `access.log`와 `error.log`가 출력된다. 도커 로그는 컨테이너의 표준 출력(STDOUT), 표준 오류(STDERR)로그를 별도 메타데이터 파일로 저장하여 아래와 같이 출력된다.

![](https://images.velog.io/images/jjewqm/post/7d9009c8-92d1-4a50-89ae-2838ea159ab3/image.png)

## 5 도커 환경 이미지 관리

### 5.1 도커 이미지 생성하기

도커 이미지 생성 방법은 3가지가 있다. 먼저 pull을 사용해 도커 허브에서 미리 만들어진 이미지를 가져오는 방법이다. 두번째는 생성된 컨테이너 변경사항으로 이미지를 만든다. 세번째 방법은 Dockerfile을 빌드하는 방법이다. Dockerfile은 도커의 특별한 DSL로 이미지를 정의하는 파일이다. Pull을 사용하는 방법은 3.2절에서 설명했으니 5장에서는 컨테이너와 Dockerfile을 이용해 이미지를 생성한다.

### 5.2 컨테이너 이용한 이미지 생성하기

도커는 `Version control system`처럼 어떤 컨테이너와 이 컨테이너 부모 이미지 간 파일 변경사항을 확인할 수 있는 `docker diff` 명령어를 제공한다. `Docker diff`는 부모 이미지와 이미지에서 생성된 컨테이너 파일 시스템 간 변경사항을 확인할 수 있다. 변경사항 좌측에 A, C 문자가 나타난다. A는 ADD, C는 Change, D는 Delete를 의미한다. Vim을 설치했기에 A /etc/vim 변경사항이 출력된다.

![](https://images.velog.io/images/jjewqm/post/eb3e9801-9a43-4603-95b4-0283df66be55/image.png)

컨테이너에서 어떤 작업을 한다고 원래 이미지가 달라지지 않는다. 기존 컨테이너에 git을 설치한 뒤, nginx 이미지에서 새로운 컨테이너를 생성해 git이 설치되어 있는지 확인한다.

![](https://images.velog.io/images/jjewqm/post/7aa5c7a5-e7ff-4f1e-8276-c6b57ac5fb66/image.png)

![](https://images.velog.io/images/jjewqm/post/fb5198a2-3b61-46c5-802e-6f43cb463ac8/image.png)

`newNginx` 이름의 새로운 컨테이너에는 git이 설치되어 있지 않다.

![](https://images.velog.io/images/jjewqm/post/e07b9ae6-9888-4e15-b8bb-81a8d33122c5/image.png)

![](https://images.velog.io/images/jjewqm/post/3908eeed-dc67-4f56-877f-2d339e58e698/image.png)

기존 컨테이너에 `commit` 명령어로 git이 설치된 이미지를 생성하고 컨테이너를 실행하겠다.

![](https://images.velog.io/images/jjewqm/post/8afcd1a6-b636-4657-bf3f-58347674cd29/image.png)

![](https://images.velog.io/images/jjewqm/post/7055ed43-c64e-41d0-919a-acafb7ae9477/image.png)

`docker exec -it [ContainerID] /bin/bash` 명령어로 컨테이너에 접속한다. git이 실행된다.

![](https://images.velog.io/images/jjewqm/post/d49429b7-f9df-4331-8972-6b0179d38d66/image.png)

## 5.3 Dockerfile 이용한 이미지 생성하기

우선 `Dockerfile`을 저장하기 위한 디렉터리를 생성하고 `vim` 명령어로 `Dockerfile`을 생성한다.

![](https://images.velog.io/images/jjewqm/post/1832d424-ae2a-4fe2-896f-dddc80f5db6c/image.png)

아래와 같이 `Dockerfile`을 작성한다. `FROM`은 어떤 이미지로부터 이미지를 생성할지 결정한다. `RUN`은 명령어를 실행하라는 의미다. `&&`은 여러 명령어를 이어서 실행하는 연산자다. \은 명령어를 여러 줄에 작성하는 문자다. `Dockerfile` 한 줄 한 줄은 레이어라는 형태로 저장되기 때문에 `RUN` 명령어를 적게 쓰면 레이어가 줄어들고, 캐시도 효율적으로 관리할 수 있다.

```
FROM nginx:latest
RUN apt-get update &&\
apt-get install -y git
```

`Docker build -t [image name:image version] [Dockerfile Path]` 명령어로 이미지를 빌드한다.

![](https://images.velog.io/images/jjewqm/post/635ab373-b76d-4d9d-823b-b6cacd927151/image.png)

성공적으로 이미지가 생성되었으며 `git`이 실행된다.

![](https://images.velog.io/images/jjewqm/post/61921592-1e2a-4c90-af37-30ace068e2fa/image.png)

## 5.4 이미지 배포하기

도커 허브는 도커에서 제공하는 저장소로 깃허브 같은 서비스이다. 공식 이미지를 다운로드 받는 데 사용하거나 직접 만든 이미지를 업로드, 배포하는 데 사용한다. 이미지를 배포하려면 회원가입을 해야 한다. 계정이 있다면 `docker login` 명령어로 로그인 한다.

![](https://images.velog.io/images/jjewqm/post/28a4e20f-4320-431b-ad1e-05f140a694d5/image.png)

앞서 도커 허브에 업로드할 Nginx 이미지 이름을 `nginx:git-from-dockerfile`로 지었다. 이미지를 업로드 하려면 기존 이미지 이름에 도커 허브 아이디를 추가해야 한다. `Docker tag 기존 이미지 이름:태그 DOCKER_HUB_ID/기존 이미지 이름:태그명령어`로 이미지 이름을 변경한다.

![](https://images.velog.io/images/jjewqm/post/637e9127-c590-4395-b5c3-d7b338b15d66/image.png)

![](https://images.velog.io/images/jjewqm/post/a2ea72c8-a7d2-44da-949d-25953d88c71e/image.png)

이름이 변경되었으면 업로드한다. 업로드한 이미지는 도커 허브 공개 저장소로 등록된다.

![](https://images.velog.io/images/jjewqm/post/e115606c-95d7-45b5-a49f-a78b5ee6b764/image.png)

이름 규칙만 맞으면 도커 허브는 `[DOCKER_HUB_ID]/nginx` 이미지 저장소가 없더라도, 푸시 작업 과정에서 이미지를 생성한다. 아래와 같이 도커 허브에서 업로드한 이미지를 확인할 수 있다.

![](https://images.velog.io/images/jjewqm/post/15f16263-1375-4d5d-abc7-d40ecd3cf897/image.png)
