double degrees_to_radians(double degrees);
double* q8_conjugate(double q[]);
double* q8_exponentiate(double q[]);
double* q8_inverse(double q[]);
double* q8_multiply(double q1[], double q2[]);
double* q8_multiply2(double q1[], double q2[]);
double q8_norm(double q[]);
double* q8_normal_01(int* seed);
void q8_transpose_print(double q[], char* title);
double r8_acos(double c);
double* r8mat_mv_new(int m, int n, double a[], double x[]);
void r8mat_print(int m, int n, double a[], char* title);
void r8mat_print_some(int m, int n, double a[], int ilo, int jlo, int ihi,
	int jhi, char* title);
double* r8vec_copy_new(int n, double a1[]);
double* r8vec_cross_product(double v1[3], double v2[3]);
double r8vec_dot_product(int n, double a1[], double a2[]);
double r8vec_norm(int n, double a[]);
void r8vec_print(int n, double a[], char* title);
double* r8vec_uniform_01_new(int n, int* seed);
double* r8vec_zeros_new(int n);
double radians_to_degrees(double angle);
double* rotation_axis_vector(double axis[3], double angle, double v[3]);
double* rotation_axis2mat(double axis[3], double angle);
double* rotation_axis2quat(double axis[3], double angle);
double* rotation_mat_vector(double a[3 * 3], double v[3]);
void rotation_mat2axis(double a[3 * 3], double axis[3], double* angle);
double* rotation_mat2quat(double a[3 * 3]);
double* rotation_quat_vector(double q[4], double v[3]);
void rotation_quat2axis(double q[4], double axis[3], double* angle);
double* rotation_quat2mat(double q[4]);
void timestamp();
