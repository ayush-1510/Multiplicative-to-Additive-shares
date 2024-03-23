#include "cypherock.h"

void get_hash(bignum256 *x, bignum256 *res)
{
    uint8_t in[LEN/8];
    uint8_t out[LEN/8];
    bn_write_le(x,in);
    sha3_256(in, LEN/8, out);
    bn_read_le(out, res);
}