#include "bob.h"

bignum256 b;
bignum256 d[LEN];
bignum256 d_ = {0};
static bignum256 p_kb;

//generate b
void gen_b()
{
    bn_rand(&b, &secp256k1.prime);
}

//get b
void get_b()
{
    uint64_t b_;
    scanf("%lu", &b_);
    bn_read_uint64(b_, &b);
}

void bob_p_kb()
{
    bn_rand(&p_kb, &secp256k1.prime);
}

void bob_pub_kb(int i)
{
    if(bn_testbit(&b, i))
    {
        //pub_kb=p_kb*(G)+A
        point_multiply(&secp256k1, &p_kb, &secp256k1.G, &pub_kb);
        point_add(&secp256k1, &pub_ka, &pub_kb); 
    }
    else
    {
        //pub_kb=p_kb*G
        point_multiply(&secp256k1, &p_kb, &secp256k1.G, &pub_kb);
    }
}

void decrypt(int i, bignum256 *enc_m)
{
    // Prepare decryption key kr=hash(p_kb*A)
    curve_point kr_key;
    point_multiply(&secp256k1, &p_kb, &pub_ka, &kr_key);
    bn_multiply(&kr_key.x, &kr_key.y, &secp256k1.prime);
    bignum256 kr;
    bn_mod(&kr_key.y, &secp256k1.prime);
    get_hash(&kr_key.y, &kr);

    // Decrypt the message
    if (bn_testbit(&b, i))
    {
        bn_xor(&d[i], &kr, &enc_m[1]);
    }
    else
    {
        bn_xor(&d[i], &kr, &enc_m[0]);
    }
}

void calculate_d()
{
    bn_zero(&d_);
    for (int i = 1; i <= LEN; i++)
    {
        bignum256 temp;
        bn_zero(&temp);
        bn_setbit(&temp, i);
        bn_multiply(&temp, &d[i], &secp256k1.prime);
        bn_mod(&d[i], &secp256k1.prime);
        bn_add(&d_, &d[i]);
    }

    bn_negate(&d_, &secp256k1.prime);
}