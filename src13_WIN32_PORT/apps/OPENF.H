#ifdef __cplusplus
extern "C" {
#endif
FILE *fopenSafe(char *FName,int oflags,int sflag,char *fdflags,FILE **fp,int *errn);
int sopenSafe(char *FName,int oflags,int sflag,int *fh,int *errn);
#ifdef __cplusplus
}
#endif
