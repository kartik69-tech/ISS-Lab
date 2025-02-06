def encrypt_rail_fence(text, key):
    rail = [['\n' for _ in range(len(text))] for _ in range(key)]

    direction_down = False
    row, col = 0, 0

    for char in text:
        if row == 0 or row == key - 1:
            direction_down = not direction_down

        rail[row][col] = char
        col += 1

        row += 1 if direction_down else -1

    encrypted_text = ''
    for i in range(key):
        for j in range(len(text)):
            if rail[i][j] != '\n':
                encrypted_text += rail[i][j]

    return encrypted_text


def decrypt_rail_fence(cipher, key):
    rail = [['\n' for _ in range(len(cipher))] for _ in range(key)]

    direction_down = None
    row, col = 0, 0

    for _ in range(len(cipher)):
        if row == 0:
            direction_down = True
        if row == key - 1:
            direction_down = False

        rail[row][col] = '*'
        col += 1

        row += 1 if direction_down else -1

    index = 0
    for i in range(key):
        for j in range(len(cipher)):
            if rail[i][j] == '*' and index < len(cipher):
                rail[i][j] = cipher[index]
                index += 1

    decrypted_text = ''
    row, col = 0, 0
    for _ in range(len(cipher)):
        if row == 0:
            direction_down = True
        if row == key - 1:
            direction_down = False

        if rail[row][col] != '\n':
            decrypted_text += rail[row][col]
            col += 1

        row += 1 if direction_down else -1

    return decrypted_text


def main():
    print("Rail Fence Cipher Program")
    print("1. Encrypt a message")
    print("2. Decrypt a message")
    choice = input("Enter your choice (1/2): ")

    if choice == '1':
        plaintext = input("Enter the plaintext message: ").replace(" ", "")
        key = int(input("Enter the number of rails (key): "))
        encrypted = encrypt_rail_fence(plaintext, key)
        print("\nEncrypted message:", encrypted)

    elif choice == '2':
        cipher_text = input("Enter the encrypted message: ")
        key = int(input("Enter the number of rails (key): "))
        decrypted = decrypt_rail_fence(cipher_text, key)
        print("\nDecrypted message:", decrypted)

    else:
        print("Invalid choice! Please enter 1 or 2.")

if __name__ == "__main__":
    main()
