#define DELTA_E_K_L 2
#define DELTA_E_K_1 0.048
#define DELTA_E_K_2 0.014

unsigned int rgb2hex(int, int, int);
float delta_e(float, float, float, float, float, float);
void  rgb2lab(float, float, float, float *, float *, float *);
int   closest(const unsigned int);


