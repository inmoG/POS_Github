"""
화이트 해커를 위한 암호와 해킹 part 1-4 첫 번째 암호 도구 구현하기

---------------------------------------------------------------
구현 기능 
1. 암호화 : 알파벳으로 이루어진 문장을 입력 받고, 문장에 있는 문자를 코드북으로 암호화 한다.
2. 복호화 : 코드북으로 암호화한 문장을 입력 받고, 문장에 있는 문자를 코드북으로 복호화 한다.
3. 파일 읽기 : 파일을 읽어 암호화 한다.

단, 문장에 있는 문자가 코드북에 존재하지 않으면 암호화, 복호화하지 않고 그대로 둔다.

코드북은 암호문:평문 구조로 아래와 같다. 

5 : a
2 : b
# : d
8 : e
1 : f
3 : g
4 : h
6 : i
0 : l
9 : m
* : n
% : o
= : p
( : r
) : s
; : t
? : u
@ : v
: : y
7 : 공백
"""


def makeCodebook():
    decbook = {
        "5": "a",
        "2": "b",
        "#": "d",
        "8": "e",
        "1": "f",
        "3": "g",
        "4": "h",
        "6": "i",
        "0": "l",
        "9": "m",
        "*": "n",
        "%": "o",
        "=": "p",
        "(": "r",
        ")": "s",
        ";": "t",
        "?": "u",
        "@": "v",
        ":": "y",
        "7": " ",
    }  # 복호화 코드북

    encbook = {}  # 암호화 코드북
    for key in decbook:
        val = decbook[key]
        encbook[val] = key

    return encbook, decbook


def encrypt(msg, encbook):
    for c in msg:
        if c in encbook:
            msg = msg.replace(c, encbook[c])  # c의 값이 g라면 encbook[g]에 해당하는 문자로 암호화한다.

    return msg


def decrypt(msg, decbook):
    for c in msg:
        if c in decbook:
            msg = msg.replace(c, decbook[c])

    return msg


if __name__ == "__main__":
    file = open("plain.txt", "rt")
    content = file.read()
    file.close()

    encbook, decbook = makeCodebook()  # codebook create
    content = encrypt(content, encbook)  # file encrypt

    file = open("encryption.txt", "wt+")
    file.write(content)
    file.close()

    file = open("encryption.txt", "rt")
    content = file.read()
    file.close()
    print(content)

"""
파일 읽기 전용
file = open(파일경로, 'rt') # 텍스트 읽기 모드 파일 오픈
file = open(파일경로, 'rb') # 바이너리 읽기 모드 파일 오픈

파일 쓰기 전용
file = open(파일경로, 'wt') # 텍스트 쓰기 모드 파일 오픈
file = open(파일경로, 'wb') # 바이너리 쓰기 모드 파일 오픈

파일 생성 후 읽고 쓰기 전용
file = open(파일경로, 'wt+') # 텍스트 쓰기 모드 파일 생성 후 오픈
file = open(파일경로, 'wb+') # 바이너리 쓰기 모드 파일 생성 후 오픈

위 3가지 모드는 파일이 이미 존재한다면 기존 파일을 삭제한다. 파일 맨 뒤에 내용을 추가하거나 읽으려면 추가 모드를 사용한다.
file = open(파일경로, 'at') # 텍스트 추가 모드로 파일 생성 후 오픈
file = open(파일경로, 'ab') # 바이너리 추가 모드로 파일 생성 후 오픈

file.read()
파일 모든 내용을 읽어서 문자열로 리턴한다. 파일이 매우 크면 읽다가 메모리 오류 발생 가능.

file.write()
문자열 이외 객체를 입력하면 오류 발생
"""
