"""
화이트 해커를 위한 암호와 해킹 part 1-4 첫 번째 암호 도구 구현하기

---------------------------------------------------------------
구현 기능 
1. 암호화 : 알파벳으로 이루어진 문장을 입력 받고, 문장에 있는 문자를 코드북으로 암호화 한다.
2. 복호화 : 코드북으로 암호화한 문장을 입력 받고, 문장에 있는 문자를 코드북으로 복호화 한다.

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
    # 소스코드가 시작하는 위치 like C main()
    plaintext = "I love you with all my heart"

    encbook, decbook = makeCodebook()
    ciphertext = encrypt(plaintext, encbook)
    print(ciphertext)

    deciphertext = decrypt(ciphertext, decbook)
    print(deciphertext)
