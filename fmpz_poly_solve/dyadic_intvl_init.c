/*
    Copyright (C) 2016 Elias Tsigaridas

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_poly_solve.h"

void fmpz_dyadic_intvl_init(fmpz_dyadic_intvl_t a)
{
    a->k 		= 0;
    a->sgn_left = 0;

    fmpz_init(a->c);
}
