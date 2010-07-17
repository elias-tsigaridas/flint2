/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int result;
    printf("evaluate_fmpz....");
    fflush(stdout);

    fmpq_poly_randinit();

    // Check that (f+g)(a) = f(a) + g(a)
    for (ulong i = 0; i < 10000UL; i++)
    {
        fmpz_t a;
        fmpq_poly_t f, g, h;
        mpq_t x, y;

        mpq_init(x);
        mpq_init(y);
        fmpz_init(a);
        fmpq_poly_init(f);
        fmpq_poly_init(g);
        fmpq_poly_init(h);
        fmpq_poly_randtest(f, n_randint(100), n_randint(200));
        fmpq_poly_randtest(g, n_randint(100), n_randint(200));
        fmpz_randtest(a, n_randint(100));

        fmpq_poly_evaluate_fmpz(x, f, a);
        fmpq_poly_evaluate_fmpz(y, g, a);
        mpq_add(x, x, y);
        fmpq_poly_add(h, f, g);
        fmpq_poly_evaluate_fmpz(y, h, a);

        result = (mpq_equal(x, y));
        if (!result)
        {
            printf("Error:\n");
            fmpq_poly_print(f);
            printf("\n");
            fmpq_poly_print(g);
            printf("\n");
            printf("a = ");
            fmpz_print(a);
            printf("\n");
            gmp_printf("f(a) + g(a) = %Qd\n", x);
            gmp_printf("(f + g)(a)  = %Qd\n", y);
            abort();
        }

        mpq_clear(x);
        mpq_clear(y);
        fmpz_clear(a);
        fmpq_poly_clear(f);
        fmpq_poly_clear(g);
        fmpq_poly_clear(h);
    }

    // Check that (f*g)(a) = f(a) * g(a)
    for (ulong i = 0; i < 10000UL; i++)
    {
        fmpz_t a, b, c;
        fmpq_poly_t f, g;
        mpq_t x, y;

        mpq_init(x);
        mpq_init(y);
        fmpz_init(a);
        fmpq_poly_init(f);
        fmpq_poly_init(g);
        fmpq_poly_randtest(f, n_randint(100), n_randint(200));
        fmpq_poly_randtest(g, n_randint(100), n_randint(200));
        fmpz_randtest(a, n_randint(100));

        fmpq_poly_evaluate_fmpz(x, f, a);
        fmpq_poly_evaluate_fmpz(y, g, a);
        mpq_mul(x, x, y);
        fmpq_poly_mul(f, f, g);
        fmpq_poly_evaluate_fmpz(y, f, a);

        result = (mpq_equal(x, y));
        if (!result)
        {
            printf("Error:\n");
            fmpz_print(a);
            printf("\n\n");
            abort();
        }

        mpq_clear(x);
        mpq_clear(y);
        fmpz_clear(a);
        fmpq_poly_clear(f);
        fmpq_poly_clear(g);
    }

    fmpq_poly_randclear();

    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}