#ifndef RSA_FILES_H
#define RSA_FILES_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>
#include "rsa.h"


/* RSA_PUBLIC load_public_key(QString)
 * loads public RSA key from file and returns object containing values from the
 * file
 */
RSA_PUBLIC load_public_key(QString filename) {
    // file has format:
    //  length || n  || e
    // where "||" corresponds to "\n\n"
    // bases:
    //      10 || 16 || 16
    RSA_PUBLIC pub;

    QFile file( filename );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        // throw exception should be here
        return;
    }

    QStringList lines;
    QByteArray line;
    while ( !file.atEnd() ) {
        line = file.readLine();
        lines.append( line );
    }

    if ( lines.length() != 3 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads length
    if ( mpz_set_str(pub.length, lines[0].data(), 10) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads n
    if ( mpz_set_str(pub.n, lines[1].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads e
    if ( mpz_set_str(pub.e, lines[1].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    file.close();
    return pub;
}


/* RSA_PRIVATE load_private_key(QString)
 * loads private RSA key from file and returns object containing values from the
 * file
 */
RSA_PRIVATE load_private_key(QString filename) {
    // file has format:
    //  length || p  || q  || dP || dQ || qInv
    // where "||" corresponds to "\n\n"
    // bases:
    //      10 || 16 || 16 || 16 || 16 || 16
    RSA_PRIVATE priv;

    QFile file( filename );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        // throw exception should be here
        return;
    }

    QStringList lines;
    QByteArray line;
    while ( !file.atEnd() ) {
        line = file.readLine();
        lines.append( line );
    }

    if ( lines.length() != 6 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads length
    if ( mpz_set_str(priv.length, lines[0].data(), 10) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads p
    if ( mpz_set_str(priv.p, lines[1].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads q
    if ( mpz_set_str(priv.q, lines[2].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads dP
    if ( mpz_set_str(priv.dP , lines[3].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads dQ
    if ( mpz_set_str(priv.dQ, lines[4].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    // reads qInv
    if ( mpz_set_str(priv.qInv, lines[5].data(), 16) != 0 ) {
        // throw exception should be here
        file.close();
        return;
    }

    file.close();
    return priv;
}


/* void save_public_key(RSA_PUBLIC &, QString)
 * saves one's public RSA key in specified file
 */
void save_public_key(RSA_PUBLIC &pub, QString filename) {
    // file has format:
    //  length || n  || e
    // where "||" corresponds to "\n\n"
    // bases:
    //      10 || 16 || 16

    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
        // throw exception should be here
        return;
    }

    QTextStream out( &file );

    // writes length
    out << mpz_get_str(NULL, 10, pub.length) << "\n";

    // writes n
    out << mpz_get_str(NULL, 16, pub.n) << "\n";

    // writes e
    out << mpz_get_str(NULL, 16, pub.e);

    if (file.error() != QFile::NoError) {
        // throw exception should be here
        file.close();
        return;
    }

    file.close();
}


/* void save_private_key(RSA_PRIVATE &, QString)
 * saves one's private RSA key in specified file
 */
void save_private_key(RSA_PRIVATE &priv, QString filename) {
    // file has format:
    //  length || p  || q  || dP || dQ || qInv
    // where "||" corresponds to "\n\n"
    // bases:
    //      10 || 16 || 16 || 16 || 16 || 16

    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
        // throw exception should be here
        return;
    }

    QTextStream out( &file );

    // writes length
    out << mpz_get_str(NULL, 10, priv.length) << "\n";

    // writes p
    out << mpz_get_str(NULL, 16, priv.p) << "\n";

    // writes q
    out << mpz_get_str(NULL, 16, priv.q) << "\n";

    // writes dP
    out << mpz_get_str(NULL, 16, priv.dP) << "\n";

    // writes dQ
    out << mpz_get_str(NULL, 16, priv.dQ) << "\n";

    // writes qInv
    out << mpz_get_str(NULL, 16, priv.qInv);

    if (file.error() != QFile::NoError) {
        // throw exception should be here
        file.close();
        return;
    }

    file.close();
}


#endif // RSA_FILES_H
