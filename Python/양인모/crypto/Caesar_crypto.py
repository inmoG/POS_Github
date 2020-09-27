"""
화이트 해커를 위한 암호와 해킹 part 1-5 카이사르 암호 도구 구현하기

구현 기능
1. 문장에 있는 모든 알파벳을 n만큼 이동시켜 치환한다.

"""
# global
ENC = 0  # 암호화 수행 코드
DEC = 1  # 복호화 수행 코드


def makeDisk(key):  # 암호 디스크 생성
    keytable = map(
        lambda x: (chr(x + 65), x), range(26)
    )  # (알파벳 문자, 문자 인덱스) tuple로 구성된 list >> () tuple [] list {} dict
    """
    chr() : ASCII 코드 입력받아 유니코드 문자 리턴
    range(26) 0 ~ 25 숫자를 x에 넣어 chr(x+65) >> 65 ~ 90 대문자 A ~ Z ASCII 코드 리턴
    """
    key2index = {}
    for t in keytable:
        alphabet, index = t[0], t[1]  # A, 0
        key2index[alphabet] = index  # {'A':0, 'B':1} dict create

    if key in key2index:  # if key exist key2index:
        k = key2index[key]  # k = key index
    else:
        return None, None

    enc_disk = {}
    dec_disk = {}

    for plaintext_index in range(26):  # 0 ~ 25 plaintext_index
        enc_i = (plaintext_index + k) % 26  # % = mod >> 5 = 0 + 5 % 26 | 6 = 1 + 5 % 26
        enc_ascii = enc_i + 65
        enc_disk[chr(plaintext_index + 65)] = chr(
            enc_ascii
        )  # k = 5 >> enc_disk[chr(0 + 65)] = chr(70) >> enc_disk{'A':'F'}
        # enc_disk{plain text:encryption text}
        dec_disk[chr(enc_ascii)] = chr(plaintext_index + 65)
        # dec_disk{plain text:encryption text}

    return enc_disk, dec_disk


def caesar(msg, key, mode):  # key를 사용해 msg를 암호화 또는 복호화
    ret = ""

    msg = msg.upper()
    enc_disk, dec_disk = makeDisk(key)

    if enc_disk is None:
        return ret

    if mode is ENC:
        disk = enc_disk

    if mode is DEC:
        disk = dec_disk

    for c in msg:
        if c in disk:  # c exist disk:
            ret += disk[c]  # 문자가 암호 디스크에 존재하면 암호화 또는 복호화 해 변수에 저장한다.
        else:
            ret += c  # 문자가 암호 디스크에 없으면 평문 그대로 변수에 저장한다.

    return ret


def main():
    plaintext = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    key = "F"  # makeDisk() 에서 사용하는 key, 알파벳 1개

    print(f"Original:\t{plaintext.upper()}")
    ciphertext = caesar(plaintext, key, ENC)
    print(f"Caesar Cipher: \t{ciphertext}")
    deciphertext = caesar(ciphertext, key, DEC)
    print(f"Deciphered:\t{deciphertext}")


if __name__ == "__main__":
    main()