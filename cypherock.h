#ifndef CR_H
#define CR_H

#include <stdio.h>
#include "bignum.h"
#include "ecdsa.h"
#include "secp256k1.h"
#include "curves.h"
#include "hasher.h"

#define LEN 256
extern curve_point pub_ka;
extern curve_point pub_kb;
extern int mode;

void get_hash(bignum256 *x, bignum256 *res);
void bn_rand(bignum256 *x, bignum256 *nf);
void point_subt(curve_point *pt1, curve_point *pt2, curve_point *res);

#endif