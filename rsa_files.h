/*  This file is part of Khrypto.

    Khrypto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Khrypto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Khrypto.  If not, see <http://www.gnu.org/licenses/>.
*/

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
RSA_PUBLIC load_public_key(QString filename) throw(IOErrorException);


/* RSA_PRIVATE load_private_key(QString)
 * loads private RSA key from file and returns object containing values from the
 * file
 */
RSA_PRIVATE load_private_key(QString filename) throw(IOErrorException);


/* void save_public_key(RSA_PUBLIC &, QString)
 * saves one's public RSA key in specified file
 */
void save_public_key(RSA_PUBLIC &pub, QString filename) throw(IOErrorException);


/* void save_private_key(RSA_PRIVATE &, QString)
 * saves one's private RSA key in specified file
 */
void save_private_key(RSA_PRIVATE &priv, QString filename) throw(IOErrorException);


#endif // RSA_FILES_H
