#include <locale.h>
#include <wchar.h>

#define RUSSIAN_ALPHABET_SIZE 33
#define LETTER_A_CODE 0x0430
#define K 5

void caesar_cipher_encrypt(wchar_t *buffer, int cipher_number_k) {
    int current_position = 0;
    while (buffer[current_position] != L'\0') {
        int new_alphabet_position =
            (buffer[current_position] - LETTER_A_CODE + cipher_number_k) % RUSSIAN_ALPHABET_SIZE;
        buffer[current_position] = LETTER_A_CODE + new_alphabet_position;
        current_position++;
    }
}

int main() {
    /*
     * Установление локали для отображения символов кириллицы
     */
    setlocale(LC_ALL, "");

    wchar_t buffer[64];
    wscanf(L"%ls", buffer);

    wprintf(L"Вы ввели имя\n");
    wprintf(L"%ls\n", buffer);

    caesar_cipher_encrypt(buffer, K);

    wprintf(L"Ваше зашифрованное имя\n");
    wprintf(L"%ls\n", buffer);

    caesar_cipher_encrypt(buffer, -K);

    wprintf(L"Обратно получается\n");
    wprintf(L"%ls\n", buffer);

    return 0;
}

