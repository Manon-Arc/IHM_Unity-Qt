//
// Created by ahliko on 03/05/24.
//

#ifndef IHM_HASH_H
#define IHM_HASH_H

#include <QString>

class Hash {

public:
    Hash();
    ~Hash();
    QString hashPassword(const char* password) ;
    bool verifyPassword(const QString& storedHash, const QString& password);
};


#endif //IHM_HASH_H
