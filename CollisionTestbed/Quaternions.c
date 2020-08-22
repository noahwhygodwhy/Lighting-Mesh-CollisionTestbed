# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "quaternions.h"

/******************************************************************************/

double degrees_to_radians(double degrees)

/******************************************************************************/
/*
  Purpose:

    DEGREES_TO_RADIANS converts an angle measure from degrees to radians.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    21 April 2008

  Author:

    John Burkardt

  Parameters:

    Input, double DEGREES, the angle measure in degrees.

    Output, double DEGREES_TO_RADIANS, the angle measure in radians.
*/
{
    const double r8_pi = 3.141592653589793;
    double value;

    value = (degrees / 180.0) * r8_pi;

    return value;
}
/******************************************************************************/

double* q8_conjugate(double q1[])

/******************************************************************************/
/*
  Purpose:

    Q8_CONJUGATE conjugates a quaternion.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    The conjugate of Q is

      conj ( Q ) = A - Bi - Cj - Dk.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double Q1[4], the quaternion to be conjugated.

    Output, double Q8_CONJUGATE[4], the conjugated quaternion.
*/
{
    double* q2;

    q2 = (double*)malloc(4 * sizeof(double));

    q2[0] = q1[0];
    q2[1] = -q1[1];
    q2[2] = -q1[2];
    q2[3] = -q1[3];

    return q2;
}
/******************************************************************************/

double* q8_exponentiate(double q1[])

/******************************************************************************/
/*
  Purpose:

    Q8_EXPONENTIATE exponentiates a quaternion.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    The exponential of Q can be set by
      V = sqrt ( B^2 + C^2 + D^2 )
      e^Q = e^A * ( cos ( ||V|| ) + V/||V|| sin ||V|| )

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    04 August 2018

  Author:

    John Burkardt

  Parameters:

    Input, double Q1[4], the quaternions to exponentiate.

    Output, double Q8_EXPONENTIATE[4], the exponential of the quaternion.
*/
{
    int i;
    double* q2;
    double v_norm;

    v_norm = sqrt(q1[1] * q1[1] + q1[2] * q1[2] + q1[3] * q1[3]);

    q2 = (double*)malloc(4 * sizeof(double));
    q2[0] = cos(v_norm);
    if (v_norm != 0.0)
    {
        for (i = 1; i < 4; i++)
        {
            q2[i] = sin(v_norm) * q1[i] / v_norm;
        }
    }
    else
    {
        for (i = 1; i < 4; i++)
        {
            q2[i] = 0.0;
        }
    }

    for (i = 0; i < 4; i++)
    {
        q2[i] = exp(q1[0]) * q2[i];
    }

    return q2;
}
/******************************************************************************/

double* q8_inverse(double q[])

/******************************************************************************/
/*
  Purpose:

    Q8_INVERSE inverts a quaternion.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    The inverse of Q is

      inverse ( Q ) = conjugate ( Q ) / ( norm ( Q ) )^2.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double Q[4], the quaternion to be inverted.

    Output, double QUAT_INV[4], the inverse of the input quaternion.
*/
{
    double norm;
    double* q2;

    q2 = (double*)malloc(4 * sizeof(double));

    norm = q[0] * q[0]
        + q[1] * q[1]
        + q[2] * q[2]
        + q[3] * q[3];

    q2[0] = q[0] / norm;
    q2[1] = -q[1] / norm;
    q2[2] = -q[2] / norm;
    q2[3] = -q[3] / norm;

    return q2;
}
/******************************************************************************/

double* q8_multiply(double q1[], double q2[])

/******************************************************************************/
/*
  Purpose:

    Q8_MULTIPLY multiplies two quaternions.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    To multiply two quaternions, use the relationships:

      i * j = -j * i = k
      j * k = -k * j = i
      k * i = -i * k = j
      i * i =  j * j = k * k = -1

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double Q1[4], Q2[4], the two quaternions to be multiplied.

    Output, double Q8_MULTIPLY[4], the product of the two quaternions.
*/
{
    double* q3;

    q3 = (double*)malloc(4 * sizeof(double));

    q3[0] = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3];
    q3[1] = q1[0] * q2[1] + q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2];
    q3[2] = q1[0] * q2[2] - q1[1] * q2[3] + q1[2] * q2[0] + q1[3] * q2[1];
    q3[3] = q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1] + q1[3] * q2[0];

    return q3;
}
/******************************************************************************/

double* q8_multiply2(double q1[], double q2[])

/******************************************************************************/
/*
  Purpose:

    Q8_MULTIPLY2 multiplies two quaternions using a matrix format.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    To multiply two quaternions, use the relationships:

      i * j = -j * i = k
      j * k = -k * j = i
      k * i = -i * k = j
      i * i =  j * j = k * k = -1

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    05 August 2018

  Author:

    John Burkardt

  Parameters:

    Input, double Q1[4], Q2[4], the quaternions to be multiplied.

    Output, double Q8_MULTIPLY2[4], the product of the two quaternions.
*/
{
    double* q3;
    /*
      The matrix entries are listed by column, not row.
    */
    double qm[4 * 4] = {
      q1[0],  q1[1],  q1[2],  q1[3],
     -q1[1], +q1[0], +q1[3], -q1[2],
     -q1[2], -q1[3], +q1[0], +q1[1],
     -q1[3], +q1[2], -q1[1], +q1[0] };

    q3 = r8mat_mv_new(4, 4, qm, q2);

    return q3;
}
/******************************************************************************/

double q8_norm(double q[])

/******************************************************************************/
/*
  Purpose:

    Q8_NORM computes the norm of a quaternion.

  Discussion:

    A quaternion is a quadruplet (A,B,C,D) of real numbers, which
    may be written as

      Q = A + Bi + Cj + Dk.

    The norm of Q is

      norm(Q) = sqrt ( A * A + B * B + C * C + D * D ).

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double Q[4], the quaternion.

    Output, double Q8_NORM, the norm of the quaternion.
*/
{
    double norm;

    norm = r8vec_norm(4, q);

    return norm;
}
/******************************************************************************/

double* q8_normal_01(int* seed)

/******************************************************************************/
/*
  Purpose:

    Q8_NORMAL_01 returns a normally distributed quaternion.

  Discussion:

    The normal distribution with mean 0 and variance 1 is used.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    05 August 2018

  Author:

    John Burkardt

  Parameters:

    Input/output, int *SEED, a seed for the random number
    generator.

    Output, double *Q8_NORMAL_01[4], the sampled quaternion.
*/
{
    double* q;
    double* r;
    const double r8_pi = 3.141592653589793;

    r = r8vec_uniform_01_new(4, seed);

    q = (double*)malloc(4 * sizeof(double));

    q[0] = sqrt(-2.0 * log(r[0])) * cos(2.0 * r8_pi * r[1]);
    q[1] = sqrt(-2.0 * log(r[0])) * sin(2.0 * r8_pi * r[1]);
    q[2] = sqrt(-2.0 * log(r[2])) * cos(2.0 * r8_pi * r[3]);
    q[3] = sqrt(-2.0 * log(r[2])) * sin(2.0 * r8_pi * r[3]);

    free(r);

    return q;
}
/******************************************************************************/

void q8_transpose_print(double q[], char* title)

/******************************************************************************/
/*
  Purpose:

    Q8_TRANSPOSE_PRINT prints a Q8 "transposed".

  Discussion:

    A Q8 is a quaternion using R8 arithmetic.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    05 August 2018

  Author:

    John Burkardt

  Parameters:

    Input, double Q[4], the quaternion to be printed.

    Input, char *TITLE, a title.
*/
{
    printf("%s  %g  %g  %g  %g\n", title, q[0], q[1], q[2], q[3]);

    return;
}
/******************************************************************************/

double r8_acos(double c)

/******************************************************************************/
/*
  Purpose:

    R8_ACOS computes the arc cosine function, with argument truncation.

  Discussion:

    If you call your system ACOS routine with an input argument that is
    outside the range [-1.0, 1.0 ], you may get an unpleasant surprise.
    This routine truncates arguments outside the range.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    13 June 2002

  Author:

    John Burkardt

  Parameters:

    Input, double C, the argument, the cosine of an angle.

    Output, double R8_ACOS, an angle whose cosine is C.
*/
{
    double angle;
    const double r8_pi = 3.141592653589793;

    if (c <= -1.0)
    {
        angle = r8_pi;
    }
    else if (1.0 <= c)
    {
        angle = 0.0;
    }
    else
    {
        angle = acos(c);
    }
    return angle;
}
/******************************************************************************/

double* r8mat_mv_new(int m, int n, double a[], double x[])

/******************************************************************************/
/*
  Purpose:

    R8MAT_MV_NEW multiplies a matrix times a vector.

  Discussion:

    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
    in column-major order.

    For this routine, the result is returned as the function value.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    15 April 2014

  Author:

    John Burkardt

  Parameters:

    Input, int M, N, the number of rows and columns of the matrix.

    Input, double A[M,N], the M by N matrix.

    Input, double X[N], the vector to be multiplied by A.

    Output, double R8MAT_MV_NEW[M], the product A*X.
*/
{
    int i;
    int j;
    double* y;

    y = (double*)malloc(m * sizeof(double));

    for (i = 0; i < m; i++)
    {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
        {
            y[i] = y[i] + a[i + j * m] * x[j];
        }
    }

    return y;
}
/******************************************************************************/

void r8mat_print(int m, int n, double a[], char* title)

/******************************************************************************/
/*
  Purpose:

    R8MAT_PRINT prints an R8MAT.

  Discussion:

    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
    in column-major order.

    Entry A(I,J) is stored as A[I+J*M]

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    28 May 2008

  Author:

    John Burkardt

  Parameters:

    Input, int M, the number of rows in A.

    Input, int N, the number of columns in A.

    Input, double A[M*N], the M by N matrix.

    Input, char *TITLE, a title.
*/
{
    r8mat_print_some(m, n, a, 1, 1, m, n, title);

    return;
}
/******************************************************************************/

void r8mat_print_some(int m, int n, double a[], int ilo, int jlo, int ihi,
    int jhi, char* title)

    /******************************************************************************/
    /*
      Purpose:

        R8MAT_PRINT_SOME prints some of an R8MAT.

      Discussion:

        An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
        in column-major order.

      Licensing:

        This code is distributed under the GNU LGPL license.

      Modified:

        26 June 2013

      Author:

        John Burkardt

      Parameters:

        Input, int M, the number of rows of the matrix.
        M must be positive.

        Input, int N, the number of columns of the matrix.
        N must be positive.

        Input, double A[M*N], the matrix.

        Input, int ILO, JLO, IHI, JHI, designate the first row and
        column, and the last row and column to be printed.

        Input, char *TITLE, a title.
    */
{
# define INCX 5

    int i;
    int i2hi;
    int i2lo;
    int j;
    int j2hi;
    int j2lo;

    fprintf(stdout, "\n");
    fprintf(stdout, "%s\n", title);

    if (m <= 0 || n <= 0)
    {
        fprintf(stdout, "\n");
        fprintf(stdout, "  (None)\n");
        return;
    }
    /*
      Print the columns of the matrix, in strips of 5.
    */
    for (j2lo = jlo; j2lo <= jhi; j2lo = j2lo + INCX)
    {
        j2hi = j2lo + INCX - 1;
        if (n < j2hi)
        {
            j2hi = n;
        }
        if (jhi < j2hi)
        {
            j2hi = jhi;
        }

        fprintf(stdout, "\n");
        /*
          For each column J in the current range...

          Write the header.
        */
        fprintf(stdout, "  Col:  ");
        for (j = j2lo; j <= j2hi; j++)
        {
            fprintf(stdout, "  %7d     ", j - 1);
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "  Row\n");
        fprintf(stdout, "\n");
        /*
          Determine the range of the rows in this strip.
        */
        if (1 < ilo)
        {
            i2lo = ilo;
        }
        else
        {
            i2lo = 1;
        }
        if (m < ihi)
        {
            i2hi = m;
        }
        else
        {
            i2hi = ihi;
        }

        for (i = i2lo; i <= i2hi; i++)
        {
            /*
              Print out (up to) 5 entries in row I, that lie in the current strip.
            */
            fprintf(stdout, "%5d:", i - 1);
            for (j = j2lo; j <= j2hi; j++)
            {
                fprintf(stdout, "  %14g", a[i - 1 + (j - 1) * m]);
            }
            fprintf(stdout, "\n");
        }
    }

    return;
# undef INCX
}
/******************************************************************************/

double* r8vec_copy_new(int n, double a1[])

/******************************************************************************/
/*
  Purpose:

    R8VEC_COPY_NEW copies an R8VEC.

  Discussion:

    An R8VEC is a vector of R8's.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    26 August 2008

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of entries in the vectors.

    Input, double A1[N], the vector to be copied.

    Output, double R8VEC_COPY_NEW[N], the copy of A1.
*/
{
    double* a2;
    int i;

    a2 = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        a2[i] = a1[i];
    }
    return a2;
}
/******************************************************************************/

double* r8vec_cross_product(double v1[3], double v2[3])

/******************************************************************************/
/*
  Purpose:

    R8VEC_CROSS_PRODUCT computes the cross product of two R8VEC's in 3D.

  Discussion:

    An R8VEC is a vector of R8's.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    20 July 2010

  Author:

    John Burkardt

  Parameters:

    Input, double V1[3], V2[3], the coordinates of the vectors.

    Output, double R8VEC_CROSS_PRODUCT[3], the cross product vector.
*/
{
    double* v3;

    v3 = (double*)malloc(3 * sizeof(double));

    v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
    v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
    v3[2] = v1[0] * v2[1] - v1[1] * v2[0];

    return v3;
}
/******************************************************************************/

double r8vec_dot_product(int n, double a1[], double a2[])

/******************************************************************************/
/*
  Purpose:

    R8VEC_DOT_PRODUCT computes the dot product of a pair of R8VEC's.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    26 July 2007

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of entries in the vectors.

    Input, double A1[N], A2[N], the two vectors to be considered.

    Output, double R8VEC_DOT_PRODUCT, the dot product of the vectors.
*/
{
    int i;
    double value;

    value = 0.0;
    for (i = 0; i < n; i++)
    {
        value = value + a1[i] * a2[i];
    }
    return value;
}
/******************************************************************************/

double r8vec_norm(int n, double a[])

/******************************************************************************/
/*
  Purpose:

    R8VEC_NORM returns the L2 norm of an R8VEC.

  Discussion:

    The vector L2 norm is defined as:

      R8VEC_NORM = sqrt ( sum ( 1 <= I <= N ) A(I)^2 ).

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    01 March 2003

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of entries in A.

    Input, double A[N], the vector whose L2 norm is desired.

    Output, double R8VEC_NORM, the L2 norm of A.
*/
{
    int i;
    double v;

    v = 0.0;

    for (i = 0; i < n; i++)
    {
        v = v + a[i] * a[i];
    }
    v = sqrt(v);

    return v;
}
/******************************************************************************/

void r8vec_print(int n, double a[], char* title)

/******************************************************************************/
/*
  Purpose:

    R8VEC_PRINT prints an R8VEC.

  Discussion:

    An R8VEC is a vector of R8's.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    08 April 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of components of the vector.

    Input, double A[N], the vector to be printed.

    Input, char *TITLE, a title.
*/
{
    int i;

    fprintf(stdout, "\n");
    fprintf(stdout, "%s\n", title);
    fprintf(stdout, "\n");
    for (i = 0; i < n; i++)
    {
        fprintf(stdout, "  %8d: %14g\n", i, a[i]);
    }

    return;
}
/******************************************************************************/

double* r8vec_uniform_01_new(int n, int* seed)

/******************************************************************************/
/*
  Purpose:

    R8VEC_UNIFORM_01_NEW returns a unit pseudorandom R8VEC.

  Discussion:

    This routine implements the recursion

      seed = 16807 * seed mod ( 2^31 - 1 )
      unif = seed / ( 2^31 - 1 )

    The integer arithmetic never requires more than 32 bits,
    including a sign bit.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    19 August 2004

  Author:

    John Burkardt

  Reference:

    Paul Bratley, Bennett Fox, Linus Schrage,
    A Guide to Simulation,
    Second Edition,
    Springer, 1987,
    ISBN: 0387964673,
    LC: QA76.9.C65.B73.

    Bennett Fox,
    Algorithm 647:
    Implementation and Relative Efficiency of Quasirandom
    Sequence Generators,
    ACM Transactions on Mathematical Software,
    Volume 12, Number 4, December 1986, pages 362-376.

    Pierre L'Ecuyer,
    Random Number Generation,
    in Handbook of Simulation,
    edited by Jerry Banks,
    Wiley, 1998,
    ISBN: 0471134031,
    LC: T57.62.H37.

    Peter Lewis, Allen Goodman, James Miller,
    A Pseudo-Random Number Generator for the System/360,
    IBM Systems Journal,
    Volume 8, Number 2, 1969, pages 136-143.

  Parameters:

    Input, int N, the number of entries in the vector.

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R8VEC_UNIFORM_01_NEW[N], the vector of pseudorandom values.
*/
{
    int i;
    const int i4_huge = 2147483647;
    int k;
    double* r;

    if (*seed == 0)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "R8VEC_UNIFORM_01_NEW - Fatal error!\n");
        fprintf(stderr, "  Input value of SEED = 0.\n");
        exit(1);
    }

    r = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        k = *seed / 127773;

        *seed = 16807 * (*seed - k * 127773) - k * 2836;

        if (*seed < 0)
        {
            *seed = *seed + i4_huge;
        }

        r[i] = (double)(*seed) * 4.656612875E-10;
    }

    return r;
}
/******************************************************************************/

double* r8vec_zeros_new(int n)

/******************************************************************************/
/*
  Purpose:

    R8VEC_ZEROS_NEW creates and zeroes an R8VEC.

  Discussion:

    An R8VEC is a vector of R8's.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    25 March 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N, the number of entries in the vector.

    Output, double R8VEC_ZEROS_NEW[N], a vector of zeroes.
*/
{
    double* a;
    int i;

    a = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        a[i] = 0.0;
    }
    return a;
}
/******************************************************************************/

double radians_to_degrees(double angle)

/******************************************************************************/
/*
  Purpose:

    RADIANS_TO_DEGREES converts an angle from radians to degrees.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    27 August 2003

  Author:

    John Burkardt

  Parameters:

    Input, double ANGLE, an angle in radians.

    Output, double RADIANS_TO_DEGREES, the equivalent angle in degrees.
*/
{
    const double r8_pi = 3.141592653589793;
    double value;

    value = (angle / r8_pi) * 180.0;

    return value;
}
/******************************************************************************/

double* rotation_axis_vector(double axis[3], double angle, double v[3])

/******************************************************************************/
/*
  Purpose:

    ROTATION_AXIS_VECTOR rotates a vector around an axis vector in 3D.

  Discussion:

    Thanks to Cody Farnell for correcting some mistakes in an earlier
    version of this routine.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double AXIS[3], the axis vector for the rotation.

    Input, double ANGLE, the angle, in radians, of the rotation.

    Input, double V[3], the vector to be rotated.

    Output, double ROTATION_AXIS_VECTOR[3], the rotated vector.
*/
{
    double axis_norm;
    double dot;
    double norm;
    double normal[3];
    double normal_component;
    double* normal2;
    double parallel[3];
    double rot[3];
    double* u;
    double* w;
    /*
      Compute the length of the rotation axis.
    */
    u = r8vec_copy_new(3, axis);

    axis_norm = r8vec_norm(3, u);

    if (axis_norm == 0.0)
    {
        free(u);
        w = r8vec_zeros_new(3);
        return w;
    }

    u[0] = u[0] / axis_norm;
    u[1] = u[1] / axis_norm;
    u[2] = u[2] / axis_norm;
    /*
      Compute the dot product of the vector and the unit rotation axis.
    */
    dot = r8vec_dot_product(3, u, v);
    /*
      Compute the parallel component of the vector.
    */
    parallel[0] = dot * u[0];
    parallel[1] = dot * u[1];
    parallel[2] = dot * u[2];
    /*
      Compute the normal component of the vector.
    */
    normal[0] = v[0] - parallel[0];
    normal[1] = v[1] - parallel[1];
    normal[2] = v[2] - parallel[2];

    normal_component = r8vec_norm(3, normal);

    if (normal_component == 0.0)
    {
        free(u);
        w = r8vec_copy_new(3, parallel);
        return w;
    }

    normal[0] = normal[0] / normal_component;
    normal[1] = normal[1] / normal_component;
    normal[2] = normal[2] / normal_component;
    /*
      Compute a second vector, lying in the plane, perpendicular
      to V, and forming a right-handed system.
    */
    normal2 = r8vec_cross_product(u, normal);

    norm = r8vec_norm(3, normal2);

    normal2[0] = normal2[0] / norm;
    normal2[1] = normal2[1] / norm;
    normal2[2] = normal2[2] / norm;
    /*
      Rotate the normal component by the angle.
    */
    rot[0] = normal_component * (cos(angle) * normal[0]
        + sin(angle) * normal2[0]);

    rot[1] = normal_component * (cos(angle) * normal[1]
        + sin(angle) * normal2[1]);

    rot[2] = normal_component * (cos(angle) * normal[2]
        + sin(angle) * normal2[2]);

    free(normal2);
    /*
      The rotated vector is the parallel component plus the rotated component.
    */
    w = (double*)malloc(3 * sizeof(double));

    w[0] = parallel[0] + rot[0];
    w[1] = parallel[1] + rot[1];
    w[2] = parallel[2] + rot[2];

    free(u);

    return w;
}
/******************************************************************************/

double* rotation_axis2mat(double axis[3], double angle)

/******************************************************************************/
/*
  Purpose:

    ROTATION_AXIS2MAT converts a rotation from axis to matrix format in 3D.

  Discussion:

    The two dimensional array A is stored as a one dimensional vector, by columns.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Reference:

    James Foley, Andries vanDam, Steven Feiner, John Hughes,
    Computer Graphics, Principles and Practice,
    Second Edition,
    Addison Wesley, 1990.

  Parameters:

    Input, double AXIS[3], the axis vector which remains unchanged by
    the rotation.

    Input, double ANGLE, the angular measurement of the rotation about
    the axis, in radians.

    Output, double ROTATION_AXIS2MAT[3*3], the rotation matrix.
*/
{
    double* a;
    double ca;
    double norm;
    double sa;
    double v1;
    double v2;
    double v3;

    v1 = axis[0];
    v2 = axis[1];
    v3 = axis[2];

    norm = sqrt(v1 * v1 + v2 * v2 + v3 * v3);

    if (norm == 0.0)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "ROTATION_AXIS2MAT - Fatal error!\n");
        fprintf(stderr, "  Axis vector has zero norm.\n");
        exit(1);
    }

    v1 = v1 / norm;
    v2 = v2 / norm;
    v3 = v3 / norm;

    ca = cos(angle);
    sa = sin(angle);

    a = (double*)malloc(3 * 3 * sizeof(double));

    a[0 + 0 * 3] = v1 * v1 + ca * (1.0 - v1 * v1);
    a[1 + 0 * 3] = (1.0 - ca) * v2 * v1 + sa * v3;
    a[2 + 0 * 3] = (1.0 - ca) * v3 * v1 - sa * v2;

    a[0 + 1 * 3] = (1.0 - ca) * v1 * v2 - sa * v3;
    a[1 + 1 * 3] = v2 * v2 + ca * (1.0 - v2 * v2);
    a[2 + 1 * 3] = (1.0 - ca) * v3 * v2 + sa * v1;

    a[0 + 2 * 3] = (1.0 - ca) * v1 * v3 + sa * v2;
    a[1 + 2 * 3] = (1.0 - ca) * v2 * v3 - sa * v1;
    a[2 + 2 * 3] = v3 * v3 + ca * (1.0 - v3 * v3);

    return a;
}
/******************************************************************************/

double* rotation_axis2quat(double axis[3], double angle)

/******************************************************************************/
/*
  Purpose:

    ROTATION_AXIS2QUAT converts a rotation from axis to quaternion format in 3D.

  Discussion:

    A rotation quaternion Q has the form:

      Q = A + Bi + Cj + Dk

    where A, B, C and D are double numbers, and i, j, and k are to be regarded
    as symbolic constant basis vectors, similar to the role of the "i"
    in the representation of imaginary numbers.

    A is the cosine of half of the angle of rotation.  (B,C,D) is a
    unit vector pointing in the direction of the axis of rotation.
    Rotation multiplication and inversion can be carried out using
    this format and the usual rules for quaternion multiplication
    and inversion.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double AXIS[3], the axis vector which remains unchanged by
    the rotation.

    Input, double ANGLE, the angular measurement of the rotation about
    the axis, in radians.

    Output, double ROTATION_AXIS2QUAT[4], the quaternion representing the rotation.
*/
{
    double norm;
    double* q;

    norm = r8vec_norm(3, axis);

    if (norm == 0.0)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "ROTATION_AXIS2QUAT - Fatal error!\n");
        fprintf(stderr, "  The axis vector is null.\n");
        exit(1);
    }

    q = (double*)malloc(4 * sizeof(double));

    q[0] = cos(0.5 * angle);

    q[1] = axis[0] * sin(0.5 * angle) / norm;
    q[2] = axis[1] * sin(0.5 * angle) / norm;
    q[3] = axis[2] * sin(0.5 * angle) / norm;

    return q;
}
/******************************************************************************/

double* rotation_mat_vector(double a[3 * 3], double v[3])

/******************************************************************************/
/*
  Purpose:

    ROTATION_MAT_VECTOR applies a marix rotation to a vector in 3d.

  Discussion:

    The two dimensional array A is stored as a one dimensional vector, by columns.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double A[3*3], the matrix defining the rotation.

    Input, double V[3], the vector to be rotated.

    Output, double ROTATION_MAT_VECTOR[3], the rotated vector.
*/
{
    double* w;

    w = r8mat_mv_new(3, 3, a, v);

    return w;
}
/******************************************************************************/

void rotation_mat2axis(double a[3 * 3], double axis[3], double* angle)

/******************************************************************************/
/*
  Purpose:

    ROTATION_MAT2AXIS converts a rotation from matrix to axis format in 3D.

  Discussion:

    The two dimensional array A is stored as a one dimensional vector, by columns.

    The computation is based on the fact that a rotation matrix must
    have an eigenvector corresponding to the eigenvalue of 1, hence:

      ( A - I ) * v = 0.

    The eigenvector V is the axis of rotation.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Reference:

    Jack Kuipers,
    Quaternions and Rotation Sequences,
    Princeton, 1998.

  Parameters:

    Input, double A[3*3], the rotation matrix.

    Output, double AXIS[3], the axis vector which remains unchanged by
    the rotation.

    Output, double *ANGLE, the angular measurement of the rotation about
    the axis, in radians.
*/
{
    double norm;

    norm = sqrt((a[2 + 1 * 3] - a[1 + 2 * 3]) * (a[2 + 1 * 3] - a[1 + 2 * 3])
        + (a[0 + 2 * 3] - a[2 + 0 * 3]) * (a[0 + 2 * 3] - a[2 + 0 * 3])
        + (a[1 + 0 * 3] - a[0 + 1 * 3]) * (a[1 + 0 * 3] - a[0 + 1 * 3]));

    if (norm == 0.0)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "ROTATION_MAT2AXIS - Fatal error!\n");
        fprintf(stderr, "  A is not a rotation matrix,\n");
        fprintf(stderr, "  or there are multiple axes of rotation.\n");
        exit(1);
    }

    axis[0] = (a[2 + 1 * 3] - a[1 + 2 * 3]) / norm;
    axis[1] = (a[0 + 2 * 3] - a[2 + 0 * 3]) / norm;
    axis[2] = (a[1 + 0 * 3] - a[0 + 1 * 3]) / norm;
    /*
      Find the angle.
    */
    *angle = r8_acos(0.5 *
        (a[0 + 0 * 3] + a[1 + 1 * 3] + a[2 + 2 * 3] - 1.0));

    return;
}
/******************************************************************************/

double* rotation_mat2quat(double a[3 * 3])

/******************************************************************************/
/*
  Purpose:

    ROTATION_MAT2QUAT converts a rotation from matrix to quaternion format in 3D.

  Discussion:

    The two dimensional array A is stored as a one dimensional vector, by columns.

    The computation is based on the fact that a rotation matrix must
    have an eigenvector corresponding to the eigenvalue of 1, hence:

      ( A - I ) * v = 0.

    The eigenvector V is the axis of rotation.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Reference:

    Jack Kuipers,
    Quaternions and Rotation Sequences,
    Princeton, 1998.

  Parameters:

    Input, double A[3*3], the rotation matrix.

    Output, double ROTATION_MAT2QUAT[4], the quaternion representing the rotation.
*/
{
    double angle;
    double cos_phi;
    double norm;
    double* q;
    double sin_phi;

    norm = sqrt((a[2 + 1 * 3] - a[1 + 2 * 3]) * (a[2 + 1 * 3] - a[1 + 2 * 3])
        + (a[0 + 2 * 3] - a[2 + 0 * 3]) * (a[0 + 2 * 3] - a[2 + 0 * 3])
        + (a[1 + 0 * 3] - a[0 + 1 * 3]) * (a[1 + 0 * 3] - a[0 + 1 * 3]));

    if (norm == 0.0)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, "ROTATION_MAT2QUAT - Fatal error!\n");
        fprintf(stderr, "  A is not a rotation matrix,\n");
        fprintf(stderr, "  or there are multiple axes of rotation.\n");
        exit(1);
    }

    angle = r8_acos(0.5 *
        (a[0 + 0 * 3] + a[1 + 1 * 3] + a[2 + 2 * 3] - 1.0));

    cos_phi = cos(0.5 * angle);

    sin_phi = sqrt(1.0 - cos_phi * cos_phi);

    q = (double*)malloc(4 * sizeof(double));

    q[0] = cos_phi;
    q[1] = sin_phi * (a[2 + 1 * 3] - a[1 + 2 * 3]) / norm;
    q[2] = sin_phi * (a[0 + 2 * 3] - a[2 + 0 * 3]) / norm;
    q[3] = sin_phi * (a[1 + 0 * 3] - a[0 + 1 * 3]) / norm;

    return q;
}
/******************************************************************************/

double* rotation_quat_vector(double q[4], double v[3])

/******************************************************************************/
/*
  Purpose:

    ROTATION_QUAT_VECTOR applies a quaternion rotation to a vector in 3d.

  Discussion:

    If Q is a unit quaternion that encodes a rotation of ANGLE
    radians about the vector AXIS, then for an arbitrary real
    vector V, the result W of the rotation on V can be written as:

      W = Q * V * Conj(Q)

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Parameters:

    Input, double Q[4], the quaternion defining the rotation.

    Input, double V[3], the vector to be rotated.

    Output, double ROTATION_QUAT_VECTOR[3], the rotated vector.
*/
{
    double* w;

    w = (double*)malloc(3 * sizeof(double));

    w[0] =
        (2.0 * (q[0] * q[0] + q[1] * q[1]) - 1.0) * v[0]
        + 2.0 * (q[1] * q[2] - q[0] * q[3]) * v[1]
        + 2.0 * (q[1] * q[3] + q[0] * q[2]) * v[2];

    w[1] =
        2.0 * (q[1] * q[2] + q[0] * q[3]) * v[0]
        + (2.0 * (q[0] * q[0] + q[2] * q[2]) - 1.0) * v[1]
        + 2.0 * (q[2] * q[3] - q[0] * q[1]) * v[2];

    w[2] =
        2.0 * (q[1] * q[3] - q[0] * q[2]) * v[0]
        + 2.0 * (q[2] * q[3] + q[0] * q[1]) * v[1]
        + (2.0 * (q[0] * q[0] + q[3] * q[3]) - 1.0) * v[2];

    return w;
}
/******************************************************************************/

void rotation_quat2axis(double q[4], double axis[3], double* angle)

/******************************************************************************/
/*
  Purpose:

    ROTATION_QUAT2AXIS converts a rotation from quaternion to axis format in 3D.

  Discussion:

    A rotation quaternion Q has the form:

      Q = A + Bi + Cj + Dk

    where A, B, C and D are double numbers, and i, j, and k are to be regarded
    as symbolic constant basis vectors, similar to the role of the "i"
    in the representation of imaginary numbers.

    A is the cosine of half of the angle of rotation.  (B,C,D) is a
    vector pointing in the direction of the axis of rotation.
    Rotation multiplication and inversion can be carried out using
    this format and the usual rules for quaternion multiplication
    and inversion.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    05 August 2018

  Author:

    John Burkardt

  Parameters:

    Input, double Q[4], the quaternion representing the rotation.

    Output, double AXIS[3], the axis vector which remains unchanged by
    the rotation.

    Output, double *ANGLE, the angular measurement of the rotation about
    the axis, in radians.
*/
{
    double cos_phi;
    double sin_phi;

    sin_phi = sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

    cos_phi = q[0];

    *angle = 2.0 * atan2(sin_phi, cos_phi);

    if (sin_phi == 0.0)
    {
        axis[0] = 1.0;
        axis[1] = 0.0;
        axis[2] = 0.0;
    }
    else
    {
        axis[0] = q[1] / sin_phi;
        axis[1] = q[2] / sin_phi;
        axis[2] = q[3] / sin_phi;
    }

    return;
}
/******************************************************************************/

double* rotation_quat2mat(double q[4])

/******************************************************************************/
/*
  Purpose:

    ROTATION_QUAT2MAT converts a rotation from quaternion to matrix format in 3D.

  Discussion:

    The two dimensional array A is stored as a one dimensional vector, by columns.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    30 May 2010

  Author:

    John Burkardt

  Reference:

    James Foley, Andries vanDam, Steven Feiner, John Hughes,
    Computer Graphics, Principles and Practice,
    Second Edition,
    Addison Wesley, 1990.

  Parameters:

    Input, double Q[4], the quaternion representing the rotation.

    Output, double ROTATION_QUAT2MAT[3*3], the rotation matrix.
*/
{
    double* a;
    double angle;
    double ca;
    double cos_phi;
    double sa;
    double sin_phi;
    double v1;
    double v2;
    double v3;

    sin_phi = sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

    cos_phi = q[0];

    angle = 2.0 * atan2(sin_phi, cos_phi);

    if (sin_phi == 0.0)
    {
        v1 = 1.0;
        v2 = 0.0;
        v3 = 0.0;
    }
    else
    {
        v1 = q[1] / sin_phi;
        v2 = q[2] / sin_phi;
        v3 = q[3] / sin_phi;
    }

    ca = cos(angle);
    sa = sin(angle);

    a = (double*)malloc(3 * 3 * sizeof(double));

    a[0 + 0 * 3] = v1 * v1 + ca * (1.0 - v1 * v1);
    a[1 + 0 * 3] = (1.0 - ca) * v2 * v1 + sa * v3;
    a[2 + 0 * 3] = (1.0 - ca) * v3 * v1 - sa * v2;

    a[0 + 1 * 3] = (1.0 - ca) * v1 * v2 - sa * v3;
    a[1 + 1 * 3] = v2 * v2 + ca * (1.0 - v2 * v2);
    a[2 + 1 * 3] = (1.0 - ca) * v3 * v2 + sa * v1;

    a[0 + 2 * 3] = (1.0 - ca) * v1 * v3 + sa * v2;
    a[1 + 2 * 3] = (1.0 - ca) * v2 * v3 - sa * v1;
    a[2 + 2 * 3] = v3 * v3 + ca * (1.0 - v3 * v3);

    return a;
}
/******************************************************************************/

void timestamp()

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

    static char time_buffer[TIME_SIZE];
    const struct tm* tm;
    time_t now;

    now = time(NULL);
    tm = localtime(&now);

    strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm);

    printf("%s\n", time_buffer);

    return;
# undef TIME_SIZE
}


