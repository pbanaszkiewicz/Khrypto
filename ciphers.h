#ifndef CIPHERS_H
#define CIPHERS_H

#include <QtCore>
#include <cmath>

QString caesar(QString input, int key) {
    int length = input.size();
    QString output;

    QChar c;
    for (int i=0; i<length; i++) {
        c = input[i];
        output.append( c.unicode()+key );
    }

    return output;
}
QString caesar_undo(QString input, int key) {
    return caesar(input, -key);
}

QString fence(QString input, int key) {
    key = abs(key);

    int length = input.size();
    QString result;

    for (int x=0; x<key; x++) {
        for (int i=x; i<length; i+=key) {
            result.append(input[i]);
        }
    }

    return result;
}
QString fence_undo(QString input, int key) {
    key = abs(key);

    int length = input.size();
    QString result;
    int parts = length / key;
    int rest = length % key;
    if (rest != 0) parts++;

    for (int x=0; x<parts; x++) {
        for (int i=x; i<length; i+=parts) {
            result.append(input[i]);
        }
    }
    return result;
}

QString XOR(QString input, int key) {
    key = abs(key);

    int length = input.size();
    QString result;

    QChar c;
    for (int i=0; i<length; i++) {
        c = input[i];
        result.append(c.unicode() ^ key);
    }

    return result;
}
#endif // CIPHERS_H
