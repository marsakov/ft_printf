2 warnings generated.
FAILED TESTS:

# TEST NUMBER (TYPE OF ARG)
  INSTRUCTION();
  1. your function ft_printf
  2. unix function printf
     (returned value) -->written on stdout<--

# 0044 (int)
  ft_printf("%#08x", 42);
  1. (    8) -->    0x2a<--
  2. (    8) -->0x00002a<--

# 0045 (int)
  ft_printf("%#-08x", 42);
  1. (    4) -->0x2a<--
  2. (    8) -->0x2a    <--

# 0087 (int)
  ft_printf("%#6o", 2500);
  1. (    7) -->  04704<--
  2. (    6) --> 04704<--

# 0088 (int)
  ft_printf("%-#6o", 2500);
  1. (    7) -->  04704<--
  2. (    6) -->04704 <--

# 0113 (int)
  ft_printf("% +d", 42);
  1. (    3) --> 42<--
  2. (    3) -->+42<--

# 0117 (int)
  ft_printf("%  +d", 42);
  1. (    3) --> 42<--
  2. (    3) -->+42<--

# 0123 (int)
  ft_printf("%++ d", 42);
  1. (    3) --> 42<--
  2. (    3) -->+42<--

# 0129 (int)
  ft_printf("%0+5d", 42);
  1. (    5) -->00042<--
  2. (    5) -->+0042<--

# 0169 (int)
  ft_printf("%-+10.5d", 4242);
  1. (   10) -->04242     <--
  2. (   10) -->+04242    <--
