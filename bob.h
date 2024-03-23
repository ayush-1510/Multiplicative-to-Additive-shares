#include "cypherock.h"

bignum256 b;
bignum256 d[LEN];
bignum256 d_ = {0};

void gen_b();
void get_b();
void bob_p_kb();
void bob_pub_kb(int i);
void decrypt(int i, bignum256 *enc_m);
void calculate_d();