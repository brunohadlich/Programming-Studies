def cifrar(s):
    cifrado = ''
    for c in s:
        code = ord(c) + 3
        if code > 122:
            code = code - (122 - 97)
        elif code < 97 and code > 90:
            code = code - (90 - 65)
        cifrado = cifrado + chr(code)
    return cifrado

def decifrar(s):
    decifrado = ''
    for c in s:
        code = ord(c) - 3
        if code < 65:
            code = code + (90 - 65)
        elif code > 90 and code < 97:
            code = code + (122 - 97)
        decifrado = decifrado + chr(code)
    return decifrado

def teste(s):
    cifrado = cifrar(s)
    print(cifrado)
    decifrado = decifrar(cifrado)
    print(decifrado)

teste("abcdefghijklmnopqrstuwyvxz")
teste("ABCDEFGHIJKLMNOPQRSTUWYVXZ")
