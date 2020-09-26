"""
화이트 해커를 위한 암호와 해킹의 RSA 공개키 암호 구현하기 예제
작성일 : 20/04/17
작성자 : 양인모
기능 : 공개키 알고리즘 중 하나인 RSA 공개키 암호 알고리즘을 
파이썬 코드로 구현한다.
"""
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA


def rsa_encrypt(msg):
    private_key = RSA.generate(1024)  # 개인키 생성
    public_key = private_key.publickey()  # 공개키 생성
    cipher = PKCS1_OAEP.new(public_key)
    encdata = cipher.encrypt(msg)  # 암호화
    print(f"암호화 결과 : {encdata}")

    cipher = PKCS1_OAEP.new(private_key)
    decdata = cipher.decrypt(encdata)  # 복호화
    print(f"복호화 결과 : {decdata}")


def main():
    msg = "RSA 공개키 암호 구현하기 예제"
    rsa_encrypt(msg.encode("utf-8"))


main()
