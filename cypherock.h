#ifndef CR_H
#define CR_H

#include <stdio.h>
#include "./crypto/bignum.h"
#include "./crypto/ecdsa.h"
#include "./crypto/secp256k1.h"
#include "./crypto/curves.h"
#include "./crypto/hasher.h"

#define LEN 256
#define DLEN 78
extern curve_point pub_ka;
extern curve_point pub_kb;

void get_hash(bignum256 *x, bignum256 *res);
void bn_rand(bignum256 *x, const bignum256 *nf);
void point_subt(curve_point *pt1, curve_point *pt2, curve_point *res);

#endif