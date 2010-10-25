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
