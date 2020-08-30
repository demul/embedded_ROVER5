#include <stdio.h>
#include <stdlib.h>

// 0 <= pwm < 1024
// cw = 0 or 1
#define ENCODE(encoding, pwm_l, pwm_r, cw_l, cw_r) char encoding[3];\
					 encoding[0] = 'k';\
					 encoding[1] = (char)(((pwm_l>>3)<<1) | cw_l);\
					 encoding[2] = (char)(((pwm_r>>3)<<1) | cw_r);

#define DECODE(encoding, pwm, cw) cw = encoding & (char)1;\
				  pwm = (encoding>>1)<<3;


int main(void)
{
	ENCODE(encoding, 350, 350, 0, 1);
	int pwm;
	int cw;
	printf("%c\n", encoding[0]);
	printf("%d\n", encoding[1]);
	printf("%d\n\n", encoding[2]);

	DECODE(encoding[1], pwm, cw);
	printf("%d\n", pwm);
	printf("%d\n", cw);
}
