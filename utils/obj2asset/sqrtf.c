/* Version 1.0 - Initial release */
 
/*
** $Id: sqrtf.c 3654 2005-01-24 10:38:53Z vrokas $
*/
 
#include <math.h>
#include <errno.h>
 
float get_sqrtf(const float x)
{
    float f, y;
    int n;
 
    if (x==0.0) return x;
    else if (x==1.0) return 1.0;
    else if (x<0.0)
    {
        errno=EDOM;
        return 0.0;
    }
    f=frexpf(x, &n);
    y=0.41731+0.59016*f;

    y+=f/y;
    y=ldexpf(y, -2) + f/y;
 
    if (n&1)
    {
        y*=0.7071067812;
        ++n;
    }
    return ldexpf(y, n/2);
}
 
