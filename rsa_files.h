#ifndef RSA_FILES_H
#define RSA_FILES_H


#include <QtCore>
#include <QString>
#include "rsa.h"


class IOErrorException: public QtConcurrent::Exception {
public:
    void raise() const {
        throw *this;
    }
    Exception *clone() const {
        return new IOErrorException(*this);
    }
};


/* RSA_PUBLIC load_public_key(QString)
 * loads public RSA key from file and returns object containing values from the
 * file
 */
RSA_PUBLIC load_public_key(QString filename);


/* RSA_PRIVATE load_private_key(QString)
 * loads private RSA key from file and returns object containing values from the
 * file
 */
RSA_PRIVATE load_private_key(QString filename);


/* void save_public_key(RSA_PUBLIC &, QString)
 * saves one's public RSA key in specified file
 */
void save_public_key(RSA_PUBLIC &pub, QString filename);


/* void save_private_key(RSA_PRIVATE &, QString)
 * saves one's private RSA key in specified file
 */
void save_private_key(RSA_PRIVATE &priv, QString filename);


#endif // RSA_FILES_H
