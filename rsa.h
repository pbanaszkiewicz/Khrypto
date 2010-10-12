#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <gmp.h>
using namespace std;

// TODO: make it better
// rand() % limit ?
// inline?
int randomNumber(unsigned int limit) {
    unsigned int n;
    unsigned int mask = 0xFFFFFFFF;

    while(mask > limit * 2) mask >>= 1;

    do {
        n = rand();
        n &= mask;
    } while (n >= limit);

    return n;
}


// TODO: probably redundant
//Converts integer into length-byte string representation, so for example:
//int2str(1, 4) = "00000001"
//int2str(123, 3) = "00007B"
//string int2str(mpz_t &i, unsigned int length) {
//    if (mpz_cmp_d(i, pow(256.0, (double) length)) >= 0) {
//        return string();
//    }

//    string a = mpz_get_str(NULL, 16, i);
//    if (length*2 > a.length()) {
//        string b(length*2 - a.length(), '0');
//        a = b + a;
//    }
//    return a;
//}

// TODO: really not needed because of mpz_set_str()
char* str2int(int i, int length);

typedef struct RSAPublicKey {
    mpz_t n, e;
    RSAPublicKey() {
        mpz_inits(n, e, NULL);
    }
} RSA_PUBLIC;

typedef struct RSAPrivateKey {
    mpz_t p, q, dP, dQ, qInv;
    RSAPrivateKey() {
        mpz_inits(p, q, dP, dQ, qInv, NULL);
    }
} RSA_PRIVATE;

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
        r = randomNumber(2);
        if (r==0) p_tab[i]='0';
        else p_tab[i]='1';

        r = randomNumber(2);
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

    //perhaps it's not ever going to happen
    //so the comparision is not needed
    //if (mpz_cmp_ui(e, 0) == 0) {
    //    return;
    //}

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

    mpz_clears(p, q, p1, q1, n, phi, e, gcd, d, dP, dQ, qInv, NULL);
}

/*TODO LIST:
  1. sprawdzić która metoda szyfrowania jest lepsza, która działa dobrze:
    - normalne podnoszenie do potęgi + modulo
    - czy wykorzystanie Chinese Remaining Theorem
  2. udoskonalić dzielenie tekstu jawnego na bloki i ich szyfrowanie
  3. wprowadzić session key?
  4. wprowadzić PKCS#1 w wersji 2.1?
  */

// using PKCS#1 v1.5 (http://tools.ietf.org/html/rfc2313)
// it's easier than v2.1 (http://tools.ietf.org/html/rfc3447#page-6)
// http://www.di-mgt.com.au/rsa_alg.html#pkcs1schemes
void encrypt(mpz_t &cipher, string &message, RSA_PUBLIC pub) {
    //EB = 00 || 02 || PS || 00 || D
    //k = |n|
    long long k = mpz_sizeinbase(pub.n, 2) / 8;

    //D = message, |D|<=k-11

    //PS = random octets, |PS|=k-|D|-3
    long long ps_len = k - 3 - message.length();

    string PS_tab(ps_len, '0'); int rnd;
    for (int i=0; i<ps_len; i++) {
        rnd = randomNumber(255)+1;  //ensures that rnd != 00
        PS_tab[i] = (unsigned char)(rnd);
    }

    string EB("  ");
    EB[0]=0;
    EB[1]=2;
    EB.append(PS_tab);
    EB.append(" ");
    EB[EB.length()-1] = 0; //last byte is now 00
    EB.append(message);

    string EB2(2*EB.length(), '0');
        int c, d;
        for (unsigned int i=0; i<EB.length(); i++) {
            d = int(EB[i]);
            if (d<0) d = 256 + d;

            c = (d / 16) % 16;
            (c > 9 ? c += 55 : c += 48 );
            EB2[2*i] = (unsigned char)(c);

            c = d % 16;
            (c > 9 ? c += 55 : c += 48 );
            EB2[2*i+1] = (unsigned char)(c);
        }

        //EB = EB2 == 0002 || PS || 00 || D

        mpz_t m;
        mpz_init_set_str(m, EB2.c_str(), 16);

        //cout << "EB2" << endl << EB2 << endl << endl;
        //now we have EB2 generated

        //y = x^e mod n
        //e = e(k-1)e(k-2)...e(1)e(0)
        string e_str = mpz_get_str(NULL, 2, pub.e);
        int k_e = e_str.length();

        mpz_t y, x;
        mpz_inits(y, x, NULL);
        //x == EB2
        mpz_set(x, m);
        mpz_set(y, x);

        for (long long i=1; i<k_e; i++) {
            mpz_powm_ui(y, y, 2, pub.n);
            if (e_str[i]=='1') {
                mpz_mul(y, y, x);
                mpz_mod(y, y, pub.n);
            }
        }
        mpz_set(cipher, y);

}

void decrypt(string &message, mpz_t &cipher, RSA_PRIVATE &priv) {
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
    //EB = EB2 == 0002 || PS || 00 || D
    message = "000";
    message.append(mpz_get_str(NULL, 16, m));
    //cout << message.length() << endl << endl;
    //message = mpz_get_str(NULL, 16, m);
    int msg_start = message.rfind("00") + 2;
    message = message.substr(msg_start);

    //really shitty shitty part starts here…
    int c, d;
    string msg(message.length() / 2, ' ');
    for (unsigned int i=0; i<message.length(); i+=2) {
        c = int(message[i]);
        (c >= 97 ? c-=87 : c-=48 );
        d = int(message[i+1]);
        (d >= 97 ? d-=87 : d-=48 );
        c = c * 16 + d;
        msg[0.5*i] = c;
    }
    message = msg;
}


#endif // RSA_H
