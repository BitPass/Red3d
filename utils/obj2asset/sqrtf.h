/* Version 1.0 - Initial release */
 
/*
** $Id: sqrtf.c 3654 2005-01-24 10:38:53Z vrokas $
*/

/*
* sqrtf is missing from libm in some distros...
* snaggage from debian libm sqrtf source.
* changed the prototype name so it doesnt cause a problemo for those with sqrtf in libm.
*/

#include <math.h>
#include <errno.h>
 
float get_sqrtf(const float x);
