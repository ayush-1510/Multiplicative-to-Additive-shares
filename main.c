#include "cypherock.h"
#include "alice.h"
#include "bob.h"

int main()
{
    srand(time(NULL));
    int mode = 0;
    scanf("%d", &mode);

    if (!mode)
    {
        gen_a();
        gen_b();
    }
    else 
    {
        get_a();
        get_b();
    }

    for (int i = 0; i < LEN; i++)
    {
        alice_p_ka();
        bob_p_kb();
        alice_pub_ka();
        bob_pub_kb(i);

        //get encrypted messages
        bignum256 enc_m[2];
        get_encrypted_messages(i, &enc_m);
        decrypt_messages(i, &enc_m);
    }

    calculate_c();
    calculate_d();
    validate();
}