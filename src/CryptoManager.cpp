#include "CryptoManager.h"
#include <sodium.h>

bool CryptoManager::init()
{
    return sodium_init() >= 0;
}

std::string CryptoManager::hashPassword(const std::string &plainText)
{
    char outHex[crypto_generichash_BYTES * 2 + 1];
    unsigned char hash[crypto_generichash_BYTES];

    crypto_generichash(hash, sizeof(hash), (unsigned char *)plainText.c_str(), plainText.length(), NULL, 0);
    sodium_bin2hex(outHex, sizeof(outHex), hash, sizeof(hash));

    return std::string(outHex);
}

std::string CryptoManager::encrypt(const std::string &plainText, const std::string &keyHex)
{
    unsigned char key[crypto_secretbox_KEYBYTES];
    crypto_generichash(key, sizeof(key), (unsigned char *)keyHex.c_str(), keyHex.length(), NULL, 0);

    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof(nonce));

    size_t cipherLen = crypto_secretbox_MACBYTES + plainText.length();
    unsigned char ciphertext[256]; // Suficient pentru orice parola normala
    crypto_secretbox_easy(ciphertext, (unsigned char *)plainText.c_str(), plainText.length(), nonce, key);

    unsigned char combined[512];
    std::copy(nonce, nonce + sizeof(nonce), combined);
    std::copy(ciphertext, ciphertext + cipherLen, combined + sizeof(nonce));

    char finalHex[1024];
    sodium_bin2hex(finalHex, sizeof(finalHex), combined, sizeof(nonce) + cipherLen);

    return std::string(finalHex);
}

std::string CryptoManager::decrypt(const std::string &cipherHex, const std::string &keyHex)
{
    unsigned char key[crypto_secretbox_KEYBYTES];
    crypto_generichash(key, sizeof(key), (unsigned char *)keyHex.c_str(), keyHex.length(), NULL, 0);

    unsigned char combined[512];
    size_t combinedLen;
    sodium_hex2bin(combined, sizeof(combined), cipherHex.c_str(), cipherHex.length(), NULL, &combinedLen, NULL);

    unsigned char *nonce = combined;
    unsigned char *ciphertext = combined + crypto_secretbox_NONCEBYTES;
    size_t cipherLen = combinedLen - crypto_secretbox_NONCEBYTES;

    unsigned char decrypted[256];
    if (crypto_secretbox_open_easy(decrypted, ciphertext, cipherLen, nonce, key) != 0)
        return "";

    decrypted[cipherLen - crypto_secretbox_MACBYTES] = '\0';
    return std::string((char *)decrypted);
}