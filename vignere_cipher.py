def vigenere_encrypt(plaintext, key):
    encrypted_text = ""
    key_length = len(key)
    for i, char in enumerate(plaintext):
        if char.isalpha():
            # Determine the shift based on the key
            key_char = key[i % key_length]
            shift = ord(key_char.lower()) - ord('a')
            
            # Encrypt the character
            if char.isupper():
                encrypted_char = chr((ord(char) - ord('A') + shift) % 26 + ord('A'))
            else:
                encrypted_char = chr((ord(char) - ord('a') + shift) % 26 + ord('a'))
            encrypted_text += encrypted_char
        else:
            # If it's not a letter, leave it unchanged
            encrypted_text += char
    return encrypted_text

def vigenere_decrypt(ciphertext, key):
    decrypted_text = ""
    key_length = len(key)
    for i, char in enumerate(ciphertext):
        if char.isalpha():
            # Determine the shift based on the key
            key_char = key[i % key_length]
            shift = ord(key_char.lower()) - ord('a')
            
            # Decrypt the character
            if char.isupper():
                decrypted_char = chr((ord(char) - ord('A') - shift) % 26 + ord('A'))
            else:
                decrypted_char = chr((ord(char) - ord('a') - shift) % 26 + ord('a'))
            decrypted_text += decrypted_char
        else:
            # If it's not a letter, leave it unchanged
            decrypted_text += char
    return decrypted_text

def main():
    # Take input from the user
    plaintext = input("Enter the plaintext to encrypt: ")
    key = input("Enter the key: ")

    # Encrypt the plaintext
    encrypted_text = vigenere_encrypt(plaintext, key)
    print(f"Encrypted text: {encrypted_text}")

    # Decrypt the ciphertext
    decrypted_text = vigenere_decrypt(encrypted_text, key)
    print(f"Decrypted text: {decrypted_text}")

# Run the program
if __name__ == "__main__":
    main()