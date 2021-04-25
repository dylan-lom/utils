/* SEE COPYRIGHT NOTICE IN util.c */

#define  ADVANCE_PTR(ptr, size) (ptr)++; (size)--
#define  SHIFT_ARGS() ADVANCE_PTR(argv, argc)
#define  SET_ARGV0()  argv0 = argv[0]; SHIFT_ARGS();

void     die(const char *fmt, ...);
void     edie(const char *fmt, ...);

void    *ecalloc(size_t nmemb, size_t size);

char    *str_dupe(const char *s, size_t n);
size_t   str_pushc(char *s, char c, size_t size, size_t realloc_amount);
int      str_trimr(char *s, char c, int max_num);
char    *str_concat(int count, ...);
char    *str_toupper(char *s, size_t n);
#define  STR_EALLOC(s) ecalloc((s), sizeof(char))
#define  STR_MALLOC(s) calloc((s), sizeof(char))
