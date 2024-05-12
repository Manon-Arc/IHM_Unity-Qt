//
// Created by ahliko on 03/05/24.
//

#include "hash.h"

#include <sodium.h>
#include <cstring>
#include <QCoreApplication>

Hash::Hash() {
    if (sodium_init() == -1) {
        qFatal() << "Erreur lors de l'initialisation de libsodium";
        return;
    }
}

Hash::~Hash() {

}

QString Hash::hashPassword(const char* password) {
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, sizeof(salt));

    const size_t hash_len = crypto_pwhash_STRBYTES;
    const size_t ops_limit = crypto_pwhash_OPSLIMIT_INTERACTIVE;
    const size_t mem_limit = crypto_pwhash_MEMLIMIT_INTERACTIVE;
    unsigned char hash[hash_len];

    if (crypto_pwhash_str(reinterpret_cast<char *>(hash), password, strlen(password), ops_limit, mem_limit) != 0) {
        throw std::runtime_error("Erreur lors du hachage du mot de passe");
    }

    return {reinterpret_cast<const char *>(hash)};
}

bool Hash::verifyPassword(const QString& storedHash, const QString& password) {
    QByteArray storedHashBytes = storedHash.toUtf8();
    QByteArray passwordBytes = password.toUtf8();
    return (crypto_pwhash_str_verify(storedHashBytes.constData(), passwordBytes.constData(), passwordBytes.length()) != 0);
}
