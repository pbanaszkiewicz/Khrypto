#include "rsa_files.h"
#include "rsa.h"
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>


/* RSA_PUBLIC load_public_key(QString)
 * loads public RSA key from file and returns object containing values from the
 * file
 */
RSA_PUBLIC load_public_key(QString filename) {
    // file has format:
    //  length || n  || e
    // where "||" corresponds to "\n"
    // bases:
    //      10 || 16 || 16
    RSA_PUBLIC pub;

    QFile file( filename );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        file.close();
        throw IOErrorException();
    }

    QStringList lines;
    QByteArray line;
    while ( !file.atEnd() ) {
        line = file.readLine();
        // check the end of the line (we don't want "\r" nor "\n")
        if (line.endsWith(char(10))) {
            line.chop(1);
        }
        if (line.endsWith(char(13))) {
            line.chop(1);
        }
        lines.append( line );
    }

    if ( lines.length() != 3 ) {
        file.close();
        throw IOErrorException();
    }

    // reads length
    bool ok;
    pub.length = lines[0].toUInt(&ok, 10);
    if (!ok) {
        file.close();
        throw IOErrorException();
    }

    // reads n
    if ( mpz_set_str(pub.n, lines[1].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
    }

    // reads e
    if ( mpz_set_str(pub.e, lines[2].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
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
    // where "||" corresponds to "\n"
    // bases:
    //      10 || 16 || 16 || 16 || 16 || 16
    RSA_PRIVATE priv;

    QFile file( filename );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        file.close();
        throw IOErrorException();
    }

    QStringList lines;
    QByteArray line;
    while ( !file.atEnd() ) {
        line = file.readLine();
        // check the end of the line (we don't want "\r" nor "\n")
        if (line.endsWith(char(10))) {  // "\n"
            line.chop(1);
        }
        if (line.endsWith(char(13))) {  // "\r"
            line.chop(1);
        }
        lines.append( line );
    }

    if ( lines.length() != 6 ) {
        file.close();
        throw IOErrorException();
    }

    // reads length
    bool ok;
    priv.length = lines[0].toUInt(&ok, 10);
    if (!ok) {
        file.close();
        throw IOErrorException();
    }

    // reads p
    if ( mpz_set_str(priv.p, lines[1].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
    }

    // reads q
    if ( mpz_set_str(priv.q, lines[2].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
    }

    // reads dP
    if ( mpz_set_str(priv.dP , lines[3].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
    }

    // reads dQ
    if ( mpz_set_str(priv.dQ, lines[4].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
    }

    // reads qInv
    if ( mpz_set_str(priv.qInv, lines[5].toLocal8Bit().constData(), 16) != 0 ) {
        file.close();
        throw IOErrorException();
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
    // where "||" corresponds to "\n"
    // bases:
    //      10 || 16 || 16

    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
        file.close();
        throw IOErrorException();
    }

    QTextStream out( &file );

    // writes length
    //out << mpz_get_str(NULL, 10, pub.length) << "\n";
    out << pub.length << "\n";

    // writes n
    out << mpz_get_str(NULL, 16, pub.n) << "\n";

    // writes e
    out << mpz_get_str(NULL, 16, pub.e);

    if (file.error() != QFile::NoError) {
        file.close();
        throw IOErrorException();
    }

    file.close();
}


/* void save_private_key(RSA_PRIVATE &, QString)
 * saves one's private RSA key in specified file
 */
void save_private_key(RSA_PRIVATE &priv, QString filename) {
    // file has format:
    //  length || p  || q  || dP || dQ || qInv
    // where "||" corresponds to "\n"
    // bases:
    //      10 || 16 || 16 || 16 || 16 || 16

    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
        file.close();
        throw IOErrorException();
    }

    QTextStream out( &file );

    // writes length
    //out << mpz_get_str(NULL, 10, priv.length) << "\n";
    out << priv.length << "\n";

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
        file.close();
        throw IOErrorException();
    }

    file.close();
}
