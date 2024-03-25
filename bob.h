#ifndef BOB_H
#define BOB_H

#include "cypherock.h"

void gen_b();
void get_b();
void bob_p_kb();
void bob_pub_kb(int i);
void decrypt(int i, bignum256 *enc_m);
void calculate_d();

#endif