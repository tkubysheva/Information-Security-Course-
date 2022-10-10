import random
import string

# Example
# mes: hello, world!
# encrypted mes:  XGG6:,C
# key: dbhL7kgkYHgHb

# Функция, которая для каждого вызова encrypt генерирует новый ключ
def key_generate(length):
    # Ключ состоит из uppercase и lowercase букв и чисел, которые выбираются рандомно
    letters = string.digits + string.ascii_letters
    rand_string = ''.join(random.choice(letters) for i in range(length))
    return rand_string


# Функция непосредственно кодирующая или декодирующая входное сообщение
def encrypt_and_decrypt(message, key):
    processed_message = ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(message, key))
    return processed_message


def encrypt():
    input_message = input("Enter your message here: ")
    key = key_generate(len(input_message))
    encrypted_message = encrypt_and_decrypt(input_message, key)
    encrypted_message_ord = "".join(str(ord(s)) for s in encrypted_message)
    print(f"Your encrypted message: '{encrypted_message}', (ASCII: {encrypted_message_ord}), key: {key}")
    return encrypted_message, key


def decrypt(encrypt_message, key):
    decrypt_message = encrypt_and_decrypt(encrypt_message, key)
    print(f"Your decrypted message: '{decrypt_message}', key: {key}")


choice = input("If you want to encode message enter E, if you want to decode message enter D: ")

if choice == "E":
    e_message, new_key = encrypt()
    if input("If you want to decode this message enter Y, else enter anything: ") == 'Y':
        decrypt(e_message, new_key)

elif choice == 'D':
    input_encrypted_message = input("Enter your encrypted message here: ")
    input_key = input("Enter key: ")
    decrypt(input_encrypted_message, input_key)
else:
    print(f"You enter: {choice}, I don't know, what do you mean")
