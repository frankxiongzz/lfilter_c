#include <stdio.h>
#include <stdlib.h>


static void bb_digital_float_filter(float *b, float *a, float *x, float *y, float *Z, int len_b, uint32_t len_x, int stride_X, int stride_Y)
{

	float *ptr_x = x, *ptr_y = y;
	float *ptr_Z;
	float *ptr_b = (float*)b;
	float *ptr_a = (float*)a;
	float *xn, *yn;
	const float a0 = *((float *)a);
	int n;
	uint32_t k;

	/* normalize the filter coefs only once. */
	for (n = 0; n < len_b; ++n) {
		ptr_b[n] /= a0;
		ptr_a[n] /= a0;
	}

	for (k = 0; k < len_x; k++) {
		ptr_b = (float *)b;   /* Reset a and b pointers */
		ptr_a = (float *)a;
		xn = (float *)ptr_x;
		yn = (float *)ptr_y;
		if (len_b > 1) {
			ptr_Z = ((float *)Z);
			*yn = *ptr_Z + *ptr_b  * *xn;   /* Calculate first delay (output) */
			ptr_b++;
			ptr_a++;
			/* Fill in middle delays */
			for (n = 0; n < len_b - 2; n++) {
				*ptr_Z =
					ptr_Z[1] + *xn * (*ptr_b) - *yn * (*ptr_a);
				ptr_b++;
				ptr_a++;
				ptr_Z++;
			}
			/* Calculate last delay */
			*ptr_Z = *xn * (*ptr_b) - *yn * (*ptr_a);
		}
		else {
			*yn = *xn * (*ptr_b);
		}

		ptr_y += stride_Y;      /* Move to next input/output point */
		ptr_x += stride_X;
	}

}

int main()
{

	float b[3] = { 0.00013651, 0.00027302, 0.00013651 };
	float a[3] = { 1., -1.96668139 , 0.96722743 };
	float x[10] = { 2,5,6,7,8,2,3,5,1,2 };
	float delay[2] = { 0 ,0 };
	float y[1] = {};
	for (int i = 0; i < 10; i++)
	{
		bb_digital_float_filter(b, a, &x[i], y, delay, 3, 1, 1, 1);
		printf("%f\n", y[0]);
	}

	getchar();

}


