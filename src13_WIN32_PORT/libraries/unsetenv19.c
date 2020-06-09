#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "unsetenv19.h"

int unsetenv19( const char *name ) 
 /******************************/ 
{ 
 char    *buff; 
 size_t  len; 
 len = strlen( name ) + 16; 
 buff = malloc( len ); 
 sprintf( buff, "%s=", name ); 
 putenv( buff ); 
 free( buff ); 
 return( 0 ); 
} 

