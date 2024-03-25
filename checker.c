#include "checker.h"

static bignum256 r_rhs, r_lhs;
extern bignum256 a, b, c_, d_;

void print(bool t)
{
    printf(t ? "Success!\n" : "Failure!\n");
    printf("a:\n");
    bn_print(&a);
    printf("b:\n");
    bn_print(&b);
    printf("LHS = a x b :\n");
    bn_print(&r_lhs);
    printf("c:\n");
    bn_print(&c_);
    printf("d:\n");
    bn_print(&d_);
    printf("RHS = c + d :\n");
    bn_print(&r_rhs);
}

void validate()
{
    //compute rhs of result
    bn_copy(&c_, &r_rhs);
    bn_add(&r_rhs, &d_);
    bn_mod(&r_rhs, &secp256k1.prime);

    //compute lhs of result
    bn_copy(&r_lhs, &r_lhs);
    bn_multiply(&b, &r_lhs, &secp256k1.prime);
    bn_mod(&r_rhs, &secp256k1.prime);

    //compare lhs and rhs
    print(bn_is_equal(&r_rhs, &r_lhs));
}