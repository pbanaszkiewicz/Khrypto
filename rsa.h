#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <gmp.h>
using namespace std;

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

//Converts integer into length-byte string representation, so for example:
//int2str(1, 4) = "00000001"
//int2str(123, 3) = "00007B"
string int2str(mpz_t &i, unsigned int length) {
    if (mpz_cmp_d(i, pow(256.0, (double) length)) >= 0) {
        return string();
    }

    string a = mpz_get_str(NULL, 16, i);
    if (length*2 > a.length()) {
        string b(length*2 - a.length(), '0');
        a = b + a;
    }
    return a;
}

// TODO: really not needed because of mpz_set_str()
char* str2int(int i, int length);

void key_generation(int length) {
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
    while ( mpz_probab_prime_p(p, 1000)==0 ) {
        mpz_add_ui(p, p, 2L);
    }
    //if q not prime, then +=2 and try again
    while ( mpz_probab_prime_p(q, 1000)==0 ) {
        mpz_add_ui(q, q, 2L);
    }

    //swap values if and only if p > q
    //will be used later (see CRT - Chinese Remainder Theorem)
    if (mpz_cmp(p, q) < 0) {
        mpz_t tmp;
        mpz_init_set(tmp, p);
        mpz_set(p, q);
        mpz_set(q, tmp);
        mpz_clear(tmp);
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

    mpz_t d, a; //"a" is just a hack, not used anywhere in algorithm
    mpz_inits(d, a, NULL);

    //d:
    //probably redundant
    mpz_gcdext(gcd, d, NULL, e, phi);
    if (mpz_cmp_ui(d,0) < 0)
        mpz_mod(d, d, phi);

    //mpz_clears(phi, p, q, gcd, a);

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
    //private key:
    //(n, d)  OR  (p, q, dP, dQ, qInv)
}

// using PKCS#1 v1.5 (http://tools.ietf.org/html/rfc2313)
// it's easier than v2.1 (http://tools.ietf.org/html/rfc3447#page-6)
// http://www.di-mgt.com.au/rsa_alg.html#pkcs1schemes
void encrypt() {

}

void decrypt();

#endif // RSA_H
