#include "cypherock.h"

void get_hash(bignum256 *x, bignum256 *res)
{
    //convert bignum256 to uint8_t
    uint8_t in[LEN / 8];
    bn_write_le(&x, &in);
    uint8_t out[LEN / 8];

    //hash the input
    sha3_256(&in, LEN / 8, &out);

    //convert uint8_t to bignum256
    bn_read_le(&out, &res);
}

void bn_rand(bignum256 *x, bignum256 *nf)
{
    uint8_t arr[LEN/8];
    int temp;
    for (int i = 0; i < LEN / 8; i++)
    {
        //Taking modulus 4 for updating the random number temp, 
        //as a 32 bit number will get exhausted with randomness after every 3 times shift by 8 bytes
        //Why 8 bytes? Because the array we need to send has 32 size of 8 bit integers each
        //Every symbol of hexadecimal number represents 4 bit number 
        if (!(i%4))
            temp = rand();
        arr[i] = ((temp >> (i % 4)) * 8) & 0xff;
    }
    bn_read_le(&arr, &x);
    bn_mod(&x, &secp256k1.prime);
}

void bn_negate(curve_point *pt1, curve_point *2, )
{

}