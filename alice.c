#include "alice.h"

bignum256 a;
bignum256 c[LEN];
bignum256 c_ = {0};

static const bignum256 p_ka;

//generate a
void gen_a()
{
    bn_rand(&a, &secp256k1.prime); 
}

//get a
void get_a()
{
    uint64_t a_;
    scanf("%lu", &a_);
    bn_read_uint64(a_, &a);
}

//get alice private key
void alice_p_ka()
{
    bn_rand(&p_ka, &secp256k1.prime);
}

//get alice public key
void alice_pub_ka()
{
    point_multiply(&secp256k1, &p_ka, &secp256k1.G, &pub_ka);
}

void get_encrypted_messages(int i, bignum256 *enc_m)
{
    //PREPARE MESSAGES

    //declare the messages m0 and m1
    bignum256 m0, m1;

    //m0=random number c[idx]
    bn_rand(&m0, &secp256k1.prime);
    bn_copy(&m0, &c[i]);
    bn_copy(&m0, &m1);

    //m1=m0+a
    bn_add(&m1, &a);

    //PREPARE KEYS FOR ENCRYPTION

    //Declare k0 and k1 keys
    curve_point key0, key1;
    bignum256 k0, k1;

    //k0=hash(p_ka*pub_kb)
    point_multiply(&secp256k1, &p_ka, &pub_kb, &key0);
    bn_multiply(&key0.x, &key0.y, &secp256k1.prime);
    bn_mod(&key0.y, &secp256k1.prime);
    get_hash(&key0.y, &k0); 

    //k1=hash(p_ka*(pub_kb-pub_a))
    curve_point temp;
    point_subt(&pub_kb, &pub_ka, &temp);
    point_multiply(&secp256k1, &p_ka, &temp, &key1);
    bn_multiply(&key1.x, &key1.y, &secp256k1.prime);
    bn_mod(&key1.y, &secp256k1.prime);
    get_hash(&key1.y, &k1);

    //ENCRYPT MESSAGES
    bn_xor(&enc_m[0], &m0, &k0);
    bn_xor(&enc_m[1], &m1, &k1);
}

void calculate_c()
{
    bn_zero(&c_);
    for (int i = 1; i <= LEN; i++)
    {
        bignum256 temp;
        bn_zero(&temp);
        bn_setbit(&temp, i);
        bn_multiply(&temp, &c[i], &secp256k1.prime);
        bn_mod(&c[i], &secp256k1.prime);
        bn_add(&c_, &c[i]);
    }

    bignum256 temp;
    bn_zero(&temp);
    bn_subtract(&temp, &c_, &c_);
}