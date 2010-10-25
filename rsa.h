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

#ifndef RSA_MINE_H
#define RSA_MINE_H

#include <cmath>
#include <string>
#include <cstdlib>
#include <gmp.h>
#include <list>
using namespace std;


/* RSAPublicKey
 * keeps all values needed for encrypt messages
 */
typedef struct RSAPublicKey {
    int length;
    mpz_t n, e;
    RSAPublicKey() {
        mpz_inits(n, e, NULL);
    }
} RSA_PUBLIC;


/* RSAPrivateKey
 * keeps all values needed for decrypt messages
 * make sure no-one knows this, it must by highly secret
 */
typedef struct RSAPrivateKey {
    int length;
    mpz_t p, q, dP, dQ, qInv;
    RSAPrivateKey() {
        mpz_inits(p, q, dP, dQ, qInv, NULL);
    }
} RSA_PRIVATE;


/* int random(unsigned int)
 * fastest function for generating random values I found
 */
inline int random(unsigned int);


/* string decbyte2hex(int)
 * convert an integer N, 0 <= N < 256 to the number in base 16
 */
string decbyte2hex(int);


/* int hex2decbyte(char, char)
 * convert a number in base 16 to the integer N, 0 <= N < 256
 */
int hex2decbyte(char, char);


/* void key_generation(int, RSA_PRIVATE, RSA_PUBLIC)
 * generate keys for encrypting and decrypting messages
 * see more at  http://tools.ietf.org/html/rfc2313
 */
void key_generation(int, RSA_PRIVATE &, RSA_PUBLIC &);


/* void RSA_encrypt_chunk(mpz_t, string, RSA_PUBLIC)
 * encrypts one part of message using one's public key, part fits the
 * requirements for itself, so that |part| <= k - 11
 */
void RSA_encrypt_chunk(mpz_t &, string &, RSA_PUBLIC &);


/* void RSA_decrypt_chunk(string, mpz_t, RSA_PRIVATE)
 * decrypts cipher using one's private key
 */
void RSA_decrypt_chunk(string &, mpz_t &, RSA_PRIVATE &);


/* void RSA_encrypt(string, list<string>, RSA_PUBLIC)
 * encrypts the whole message, slicing it into chunks if necessarily
 * the chunks are located in the list
 */
void RSA_encrypt(string, list<string> &, RSA_PUBLIC &);


/* void RSA_decrypt(string, list<string>, RSA_PRIVATE)
 * decrypts every single item from the list and appends the result to the message
 */
void RSA_decrypt(string &, list<string> &, RSA_PRIVATE &);


#endif // RSA_MINE_H
