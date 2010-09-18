#ifndef RSA_H
#define RSA_H

#include <cmath>
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

void key_generation(int length) {
    mpz_t p, q;
    mpz_init2(p, length/2);
    mpz_init2(q, length/2);

    //generate a random number of bit, set two highest bits and one lowest
    char p_tab[length/2];
    p_tab[0] = p_tab[1] = p_tab[length/2 -1] = '1';
    char q_tab[length/2];
    q_tab[0] = q_tab[1] = q_tab[length/2 -1] = '1';

    //generating random bits
    for (int i=2; i<(length/2 -1); i++) {
        int r = randomNumber(2);
        if (r==0) p_tab[i]='0';
        else p_tab[i]='1';

        r = randomNumber(2);
        if (r==0) q_tab[i]='0';
        else q_tab[i]='1';
    }

    mpz_set_str(p, p_tab, 2);
    mpz_set_str(q, q_tab, 2);

    //if p not prime, then +=2 and try again
    while ( mpz_probab_prime_p(p, 1000)==0 ) {
        mpz_add_ui(p, p, 2L);
    }
    //if q not prime, then +=2 and try again
    while ( mpz_probab_prime_p(q, 1000)==0 ) {
        mpz_add_ui(q, q, 2L);
    }

    //swap values if and only if p > q
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

    mpz_mul(n, p, q); //this is now modulus

    //just temporary subtraction
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);

    //calculating e: 1 < e < phi, gcd(e, phi) == 1
    mpz_t e, gcd;
    mpz_inits(e, gcd);
    unsigned int gcd_tab[] = {65537, 17, 3};
    for (int i=0; i<3; i++) {
        mpz_gcd_ui(gcd, phi, gcd_tab[i]);
        if (mpz_cmp_ui(gcd, 1) == 0) {
            mpz_set_ui(e, gcd_tab[i]);
            break;
        }
    }

    if (mpz_cmp_ui(e, 0) == 0) {
        //przekichane
        //bo nie ma policzonego e
        return;
    }

    mpz_t d, a; //"a" is just a hack, not used anywhere in algorithm
    mpz_inits(d, a);
    mpz_gcdext(gcd, d, a, e, phi);

    mpz_clears(phi, p, q, gcd, a);
    //now we have keys
    //public one:
    //(n, e)
    //private one:
    //(n, d)
}

// using PKCS#1 v2.1
// fuck it's hard
void encrypt() {

}

void decrypt();

struct Primes {
    mpz_t a, b;
};

//n = p * q;
//phi = (p-1)*(q-1)
//wybranie liczby E (1 < e < phi), E względnie pierwsze z phi
//wyliczenie jakiegoś d dziwnego ...

#endif // RSA_H
