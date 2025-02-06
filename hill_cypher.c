import numpy as np  

substitution = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,  
                'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18,  
                'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25}  

inverse_substitution = {value: key for key, value in substitution.items()}  

def mod_inverse(a, m=26):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return None 
def matrix_inverse(matrix):
    det = int(np.round(np.linalg.det(matrix))) % 26
    det_inv = mod_inverse(det)
    
    if det_inv is None:
        raise ValueError("Matrix is not invertible modulo 26.")
    
    matrix_adj = np.round(np.linalg.inv(matrix) * det).astype(int) % 26
    return (det_inv * matrix_adj) % 26

def encrypt(plain_text, key_matrix):
    plain_text = plain_text.upper()
    plain_text = plain_text.replace(" ", "")  # Remove spaces
    
    if len(plain_text) % len(key_matrix) != 0:
        padding_length = len(key_matrix) - (len(plain_text) % len(key_matrix))
        plain_text += 'X' * padding_length
    cipher_text = ''
    
    for i in range(0, len(plain_text), len(key_matrix)):
        block = plain_text[i:i+len(key_matrix)]
        block_vector = np.array([substitution[ch] for ch in block])
        
        encrypted_vector = np.dot(key_matrix, block_vector) % 26
        encrypted_block = ''.join([inverse_substitution[num] for num in encrypted_vector])
        
        cipher_text += encrypted_block
    
    return cipher_text

def decrypt(cipher_text, key_matrix):
    key_matrix_inv = matrix_inverse(key_matrix)  # Inverse of key matrix
    
    plain_text = ''
    
    for i in range(0, len(cipher_text), len(key_matrix)):
        block = cipher_text[i:i+len(key_matrix)]
        block_vector = np.array([substitution[ch] for ch in block])
        
        decrypted_vector = np.dot(key_matrix_inv, block_vector) % 26
        decrypted_block = ''.join([inverse_substitution[num] for num in decrypted_vector])
        
        plain_text += decrypted_block
    
    return plain_text

def main():
    plain_text = input("Enter the message to be encrypted: ").upper().strip()
    
    matrix_size = int(input("Enter the size of the key matrix (e.g., 2 for 2x2): "))
    key_matrix = []
    
    print(f"Enter the {matrix_size}x{matrix_size} key matrix (row by row):")
    for i in range(matrix_size):
        row = list(map(int, input(f"Enter row {i+1}: ").split()))
        key_matrix.append(row)
    
    key_matrix = np.array(key_matrix)

    cipher_text = encrypt(plain_text, key_matrix)
    print("Cipher Text:", cipher_text)

    decrypted_text = decrypt(cipher_text, key_matrix)
    print("Decrypted Text:", decrypted_text)

if __name__ == "__main__":
    main()

