#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <string>
#include <cstdlib>
#include <gmp.h>
#include <list>
using namespace std;

//TODO: make docs
typedef struct RSAPublicKey {
    int length;
    mpz_t n, e;
    RSAPublicKey() {
        mpz_inits(n, e, NULL);
    }
} RSA_PUBLIC;

//TODO: make docs
typedef struct RSAPrivateKey {
    int length;
    mpz_t p, q, dP, dQ, qInv;
    RSAPrivateKey() {
        mpz_inits(p, q, dP, dQ, qInv, NULL);
    }
} RSA_PRIVATE;

//TODO: make docs
inline int random(unsigned int limit) {
    return rand() % limit;
}

//TODO: make docs
//TODO: test if it works faster with mpz_get_str or similar ;]
string decbyte2hex(int n) {
    string result = "00";
    int c;
    c = (n / 16) % 16;
    (c > 9 ? c += 55 : c += 48);
    result[0] = (unsigned char)c;
    c = n % 16;
    (c > 9 ? c += 55 : c += 48);
    result[1] = (unsigned char)c;
    return result;
}

//TODO: make docs
//TODO: test if it works faster with mpz_get_str or similar ;]
int hex2decbyte(char s0, char s1) {
    int result = 0;
    int c=int(s0), d=int(s1);
    (c >= 97 ? c-=87 : c-=48 );
    (d >= 97 ? d-=87 : d-=48 );
    result = c * 16 + d;
    return result;
}

//TODO: make docs
void key_generation(int length, RSA_PRIVATE &priv, RSA_PUBLIC &pub) {
    mpz_t p, q, p1, q1;
    mpz_init2(p, length/2);
    mpz_init2(q, length/2);
    mpz_init2(p1, length/2);
    mpz_init2(q1, length/2);

    //generate a random number of bit, set two highest bits and one lowest
    string p_tab(length/2, '1');
    string q_tab(length/2, '1');

    //generating random bits
    int r;
    for (int i=2; i<(length/2 -1); i++) {
        r = random(2);
        if (r==0) p_tab[i]='0';
        else p_tab[i]='1';

        r = random(2);
        if (r==0) q_tab[i]='0';
        else q_tab[i]='1';
    }

    mpz_set_str(p, p_tab.c_str(), 2);
    mpz_set_str(q, q_tab.c_str(), 2);

    //if p not prime, then +=2 and try again
    while ( mpz_probab_prime_p(p, 100)==0 ) {
        mpz_add_ui(p, p, 2L);
    }
    //if q not prime, then +=2 and try again
    while ( mpz_probab_prime_p(q, 100)==0 ) {
        mpz_add_ui(q, q, 2L);
    }

    //swap values if and only if p < q
    //will be used later (see CRT - Chinese Remainder Theorem)
    if (mpz_cmp(p, q) < 0) {
        mpz_swap(p, q);
    }

    mpz_t n, phi;
    mpz_init2(n, length);
    mpz_init2(phi, length);

    //n:
    mpz_mul(n, p, q);

    //p1 = p-1
    //q1 = q-1
    //will be useful later
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);

    //e:
    //1 < e < phi, gcd(e, phi) == 1
    mpz_t e, gcd;
    mpz_inits(e, gcd, NULL);
    unsigned int gcd_tab[] = {3, 17, 65537};
    for (int i=0; i<3; i++) {
        mpz_gcd_ui(gcd, phi, gcd_tab[i]);
        if (mpz_cmp_ui(gcd, 1) == 0) {
            mpz_set_ui(e, gcd_tab[i]);
            break;
        }
    }

    mpz_t d;
    mpz_init(d);

    //d:
    //probably redundant
    mpz_gcdext(gcd, d, NULL, e, phi);
    if (mpz_cmp_ui(d,0) < 0)
        mpz_mod(d, d, phi);

    mpz_t dP, dQ, qInv;
    mpz_inits(dP, dQ, qInv, NULL);

    //dP:
    mpz_gcdext(gcd, dP, NULL, e, p1);
    if (mpz_cmp_ui(dP, 0) < 0)
        mpz_mod(dP, dP, p1);

    //dQ:
    mpz_gcdext(gcd, dQ, NULL, e, q1);
    if (mpz_cmp_ui(dQ, 0) < 0)
        mpz_mod(dQ, dQ, q1);

    //qInv:
    mpz_gcdext(gcd, qInv, NULL, q, p);
    if (mpz_cmp_ui(qInv, 0) < 0)
        mpz_mod(qInv, qInv, p);

    //public key:
    //(n, e)
    mpz_set(pub.n, n);
    mpz_set(pub.e, e);

    //private key:
    //(n, d)  OR  (p, q, dP, dQ, qInv)
    mpz_set(priv.p, p);
    mpz_set(priv.q, q);
    mpz_set(priv.dP, dP);
    mpz_set(priv.dQ, dQ);
    mpz_set(priv.qInv, qInv);

    pub.length = priv.length = length;

    mpz_clears(p, q, p1, q1, n, phi, e, gcd, d, dP, dQ, qInv, NULL);
}

/*TODO LIST:
  3. wprowadzić session key?
  4. wprowadzić PKCS#1 w wersji 2.1?
  5. IMPROVE YOUR DOCS!!!
  */
//TODO: make docs
void encrypt_chunk(mpz_t &cipher, string &message, RSA_PUBLIC pub) {
    //EB = 00 || 02 || PS || 00 || D
    //k = |n|
    long long k = mpz_sizeinbase(pub.n, 2) / 8;

    //D = message, |D|<=k-11

    //PS = random octets, |PS|=k-|D|-3
    long long ps_len = k - 3 - message.length();

    string EB("0002"); // EB = 00 || 02
    EB.reserve(k*2);

    string PS_tab; PS_tab.reserve(2*ps_len);
    for (int i=0; i<ps_len; i++) {
        PS_tab.append( decbyte2hex( random(255)+1 ) );
    }

    EB.append(PS_tab); // EB = 00 || 02 || PS
    EB.append("00");   // EB = 00 || 02 || PS || 00

    for (int i=0; i<message.length(); i++) {
        EB.append( decbyte2hex((unsigned int)message[i]) );
    } //EB = 00 || 02 || PS || 00 || D

    //now we have EB generated

    //y = x^e mod n
    //e = e(k-1)e(k-2)...e(1)e(0)
    string e_str = mpz_get_str(NULL, 2, pub.e);
    int k_e = e_str.length();

    mpz_t y, x;
    mpz_inits(y, x, NULL);
    //x == EB
    mpz_set_str(x, EB.c_str(), 16);
    mpz_set(y, x);

    for (long long i=1; i<k_e; i++) {
        mpz_powm_ui(y, y, 2, pub.n);
        if (e_str[i]=='1') {
            mpz_mul(y, y, x);
            mpz_mod(y, y, pub.n);
        }
    }
    mpz_set(cipher, y);

    mpz_clears(y, x, NULL);
}

//TODO: make docs
void decrypt_chunk(string &message, mpz_t &cipher, RSA_PRIVATE &priv) {
    mpz_t m, m1, m2, h;
    mpz_inits(m, m1, m2, h, NULL);

    mpz_powm(m1, cipher, priv.dP, priv.p);
    mpz_powm(m2, cipher, priv.dQ, priv.q);

    if (mpz_cmp(m1, m2) < 0)
        mpz_add(m1, m1, priv.p);
    mpz_sub(m1, m1, m2);
    mpz_mul(h, priv.qInv, m1);
    mpz_mod(h, h, priv.p);
    mpz_mul(h, h, priv.q);
    mpz_add(m, m2, h);

    //now we have m decrypted, but we still need to unhask
    //the message from it
    //EB = 00 || 02 || PS || 00 || D
    //message = "000";
    //message.append(mpz_get_str(NULL, 16, m));
    message = mpz_get_str(NULL, 16, m);
    int msg_start = message.rfind("00") + 2;
    message = message.substr(msg_start);

    string msg(message.length() / 2, ' ');
    for (unsigned int i=0; i<message.length(); i+=2) {
        msg[0.5*i] = (unsigned char) hex2decbyte(message[i], message[i+1]);
    }
    message = msg;

    mpz_clears(m, m1, m2, h, NULL);
}

//TODO: make docs
//include <iostream>
//using namespace std;
void encrypt(string message, list<string> &cipher, RSA_PUBLIC &pub) {
    //sprawdzenie długości message wg algorytmu
    //robienie w pętli encrypt()
    //zwrócenie wektora? tablicy? coś w ten deseń
    // ... po testach: musi być ze stringiem…

    cipher.clear();

    //maximum length of single message chunk
    // key  : length
    //512b  : 53B
    //1024b : 117B
    //2048b : 245B
    // and so on ...
    int length = (pub.length / 8) - 11;

    //parts = 1 if |msg|==length
    //parts = 2 and more  if  |msg|>length
    //parts = 0 never
    int parts = ( (message.length()-1) / length) + 1;

    string msg = message, substr, c_str;
    mpz_t c; mpz_init(c);
    //cout << "1" << endl;

    for (int i=0; i<parts; i++) {
        //encrypting chunks
        //cout << i << " " << length << endl;
        if (msg.length() > length) {
            substr = msg.substr(0, length);
            msg = msg.substr(length);
        } else {
            substr = msg;
            msg = "";
        }

        encrypt_chunk(c, substr, pub);
        //dodawanie do listy?
        c_str = mpz_get_str(NULL, 16, c);
        cipher.push_back(c_str);
    }

    //zwracanie listy?
    //nie trzeba, bo mamy przez referencję

    mpz_clear(c);
}

//TODO: make docs
void decrypt(string &message, list<string> &cipher, RSA_PRIVATE &priv) {
    list<string>::iterator iter1 = cipher.begin();
    string c_str;
    mpz_t c;
    mpz_init(c);
    message.clear();
    while ( iter1 != cipher.end() ) {
        c_str = *iter1;
        mpz_set_str(c, c_str.c_str(), 16);
        decrypt_chunk(c_str, c, priv);
        message.append(c_str);
        iter1++;
    }

    mpz_clear(c);
    //decrypt na każdym odcinku
    //połączenie wyników
}


#endif // RSA_H
