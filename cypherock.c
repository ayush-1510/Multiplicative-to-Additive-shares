#include "cypherock.h"

curve_point pub_ka;
curve_point pub_kb;
extern int mode;

char dec2pow[LEN][DLEN];

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

void point_subt(curve_point *pt1, curve_point *pt2, curve_point *res)
{
    //res=pt1-pt2;
    curve_point temp;
    bn_subtract(&secp256k1.prime, &pt2->y, &temp.y);
    bn_copy(&pt2->x, &temp.x);

    point_add(&secp256k1, &pt1, &temp);
    bn_copy(&temp.x, &res->x);
    bn_copy(&temp.y, &res->y);
}

void compute_dec2pow()
{
    dec2pow[0][0] = '1';
    for (int i = 1; i < DLEN; i++)
        dec2pow[0][i] = '0';
    int carry = 0;
    for (int i = 1; i < LEN; i++)
    {
        for (int j = 0; j < DLEN; j++)
        {
            dec2pow[i][j]=2*dec2pow[i][j-1]+carry;
            carry = dec2pow[i][j] / 10;
            dec2pow[i][j] %= 10;
        }
    }
}

void add_dec(char *a, int idx)
{
    int carry = 0;
    for (int i = 0; i < DLEN; i++)
    {
        a[i] += dec2pow[idx][i] + carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}

void bn_print(bignum256 *x)
{
    uint8_t hex[LEN / 8];
    bn_write_le(x, hex);
    int flag = 0;
    printf("\t Hexadecimal representation: \n");
    for (int i = (LEN / 8) - 1; i >= 0; i--)
    {
        if (flag |= !!hex[i] || !mode)
        printf("%02x ", hex[i]);
    }
    printf("\n");

    char dec[DLEN]={0};
    for (int i = 0; i < LEN; i++)
    {
        if (hex[i / 8] >> (i % 8))
            add_dec(dec, i);
    }
    flag = 0;
    printf("\t Decimal representation: \n");
    for (int i = DLEN - 1; i >= 0; i--)
    {
        if (flag |= !!dec[i] || !mode)
            printf("%c", dec[i] + '0');
    }
    printf("\n");
}