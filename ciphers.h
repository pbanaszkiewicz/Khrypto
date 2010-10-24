#ifndef CIPHERS_H
#define CIPHERS_H

#include <QtCore>


/* QString caesar(QString, int)
 * encrypt a text using Caesar's cipher
 */
QString caesar(QString input, int key);


/* QString caesar_undo(QString, int)
 * decrypt a text using Caesar's cipher
 */
QString caesar_undo(QString input, int key);


/* QString fence(QString, int)
 * encrypt a text using fence method
 */
QString fence(QString input, int key);


/* QString fence_undo(QString, int)
 * decrypt a text using fence method
 */
QString fence_undo(QString input, int key);


/* QString XOR(QString, int)
 * made XOR on every byte of the text with the key
 */
QString XOR(QString input, int key);


#endif // CIPHERS_H
