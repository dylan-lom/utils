#define SHIFT_ARGS() argv++; argc--;
#define SET_ARGV0()  argv0 = argv[0]; SHIFT_ARGS();

