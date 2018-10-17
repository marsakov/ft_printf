# ft_printf
This project is a copy of the original printf function of C langage.


## Features

Supports all these converters, flags and modifiers:

 Type        | Name
------------ | -------------------------------------------------------------------------------
 Converters  |  %d / %s / %S / %p / %d / %D / %i / %o / %O / %u / %U / %x / %X / %c / %C / %%
 Flags       |  # / 0 / - / +
 Modifiers   |  hh / h / l / ll / j /z

 
## Compilation

To create that library, after downloading/cloning this project, cd into the project, copy all the files from the sub folders to the root directory and finally, call make:

	git clone https://github.com/marsakov/ft_printf.git
	cd ft_printf
	make

You should see a libftprintf.a file and some object files (.o).
Now to clean up (removing the .o files and the .c files from the root), call *make clean*

## Usage

Compile your project with libftprintf.a.
Don't forget to include "ft_printf.h"

To compile with the repository main:
```
gcc -Wall -Werror -Wextra main.c libftprintf.a -Iincludes/
```

