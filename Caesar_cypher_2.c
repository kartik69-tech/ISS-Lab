#include <stdio.h>
#include <ctype.h>

void encryptText(char text[], int key);
void decryptText(char text[], int key);

int main() {
    char text[100];
    int key, choice;

    // Read the text from the user
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    // Read the key value from the user
    printf("Enter the key value: ");
    scanf("%d", &key);

    // Normalize the key to the range of the alphabet
    key = key % 26;

    // Menu to choose between encryption and decryption
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encryptText(text, key);
        printf("Encrypted text: %s\n", text);
    } else if (choice == 2) {
        decryptText(text, key);
        printf("Decrypted text: %s\n", text);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

void encryptText(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base + key + 26) % 26 + base;
        }
    }
}

void decryptText(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base - key + 26) % 26 + base;
        }
    }
}
