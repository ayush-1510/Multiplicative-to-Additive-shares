#include "cypherock.h"

bignum256 a;
bignum256 c[LEN];
bignum256 c_ = {0};

void gen_a();
void get_a();
void alice_p_ka();
void alice_pub_ka();
void get_encrypted_messages(int i, bignum256 *enc_m);
void calculate_c();