#include <stdio.h>
#include "bignum.h"
#include "ecdsa.h"
#include "secp256k1.h"
#include "curves.h"
#include "hasher.h"

#define LEN 256
curve_point pub_ka;
curve_point pub_kb;

void get_hash(bignum256 *x, bignum256 *res);