#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k, len = strlen(key);

    for (i = 0, k = 0; i < len; i++) {
        if (key[i] != 'j' && dict[key[i] - 'a'] == 0) {
            keyTable[k / SIZE][k % SIZE] = key[i];
            dict[key[i] - 'a'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i != 9 && dict[i] == 0) {
            keyTable[k / SIZE][k % SIZE] = i + 'a';
            k++;
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;

    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            }
            if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

void prepareText(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len; i += 2) {
        if (str[i] == str[i + 1]) {
            for (int j = len; j > i; j--) {
                str[j] = str[j - 1];
            }
            str[i + 1] = 'x';
            len++;
        }
    }
    if (len % 2 != 0) {
        str[len] = 'x';
        str[len + 1] = '\0';
    }
}

void encrypt(char str[], char keyTable[SIZE][SIZE]) {
    int i, pos[4];

    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, str[i], str[i + 1], pos);

        if (pos[0] == pos[2]) {
            str[i] = keyTable[pos[0]][(pos[1] + 1) % SIZE];
            str[i + 1] = keyTable[pos[2]][(pos[3] + 1) % SIZE];
        } else if (pos[1] == pos[3]) {
            str[i] = keyTable[(pos[0] + 1) % SIZE][pos[1]];
            str[i + 1] = keyTable[(pos[2] + 1) % SIZE][pos[3]];
        } else {
            str[i] = keyTable[pos[0]][pos[3]];
            str[i + 1] = keyTable[pos[2]][pos[1]];
        }
    }
}

void decrypt(char str[], char keyTable[SIZE][SIZE]) {
    int i, pos[4];

    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, str[i], str[i + 1], pos);

        if (pos[0] == pos[2]) {
            str[i] = keyTable[pos[0]][(pos[1] - 1 + SIZE) % SIZE];
            str[i + 1] = keyTable[pos[2]][(pos[3] - 1 + SIZE) % SIZE];
        } else if (pos[1] == pos[3]) {
            str[i] = keyTable[(pos[0] - 1 + SIZE) % SIZE][pos[1]];
            str[i + 1] = keyTable[(pos[2] - 1 + SIZE) % SIZE][pos[3]];
        } else {
            str[i] = keyTable[pos[0]][pos[3]];
            str[i + 1] = keyTable[pos[2]][pos[1]];
        }
    }
}

void removePadding(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == 'x' && (i == len - 1 || str[i + 1] == 'x')) {
            for (int j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
        }
    }
}

int main() {
    char key[30], str[100], keyTable[SIZE][SIZE];

    printf("Enter key: ");
    scanf("%s", key);
    printf("Enter text: ");
    scanf("%s", str);

    generateKeyTable(key, keyTable);

    printf("Original text: %s\n", str);

    prepareText(str);
    encrypt(str, keyTable);
    printf("Encrypted text: %s\n", str);

    decrypt(str, keyTable);
    removePadding(str);
    printf("Decrypted text: %s\n", str);

    return 0;
}