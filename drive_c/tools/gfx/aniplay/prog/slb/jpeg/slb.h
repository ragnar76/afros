typedef void *SHARED_LIB;

/* Old version: typedef (long)(*SLB_EXEC)( void , ... );	*/
typedef long cdecl (*SLB_EXEC)( SHARED_LIB *sl, long fn, short nargs, ... );

extern long Slbopen( char *name, char *path, long min_ver,
				SHARED_LIB *sl, SLB_EXEC *fn );
extern long Slbclose( SHARED_LIB *sl );
