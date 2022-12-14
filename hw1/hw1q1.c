//
// Created by Michael Poliakov on 4/27/21.
//
// input:  coefficients of single variable trinomial p(x), in standard form.
//         meaning: p(x) = ax^2 + bx + c, we excepting from user giving a,b,c.
//
//output:  polynomial real roots if ∃.
/*-------------------------------------------------------------------------
  Calculating trinom roots.
 -------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

#define ZERO 0.000001                     // used overcome the Floating-point error mitigation


double ensure_zero (double arg);


int main()
{
    double a, b, c, dsmta;
    do
    {
        a = b = c = 0;
        printf("Enter the coefficients of a polynomial:\n");
        if(scanf("%lf %lf %lf", &a, &b, &c) != 3)
        {
            printf("ERROR\n");
            return 1;
        }
    } while (ensure_zero(a) == 0);        // Verify a ≠ 0
    dsmta = ensure_zero((b*b)+(-4*a*c));
    if (dsmta == 0)                                 // Single root, (∆ = 0).
        printf("The root is %.2f\n", ensure_zero(-0.5 * b / a));
    else if (dsmta < 0)                             // No real roots, (∆ < 0  =>  𝓍 ∉ ℝ).
        printf("There are no roots\n");
    else                                            // Two roots, (∆ > 0).
        printf("The roots are %.2f, %.2f\n",
               ensure_zero((-b - sqrt(dsmta))/(2*a)),
               ensure_zero((-b + sqrt(dsmta))/(2*a)) );
    return 0;
}


double ensure_zero (double arg)
{
    if ((arg > -ZERO) && (arg < ZERO))
        return 0;
    else
        return arg;
}
