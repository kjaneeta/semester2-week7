# Task 3

1. Examine `task3.c`. This is a program to sum the values of integers
   specified on the command line. The function `get_values()` processes the
   command line arguments, returning a pointer to dynamically-allocated
   storage containing the specified values. The function `sum_values()` sums
   these values, returning the result as a long integer.

   Notice how this code uses assertions and the conditional logging macros
   discussed on the slides.

2. Examine `Makefile`. This is a **makefile** to handle compilation of
   `task3.c`. You do not need to understand exactly how this works just yet,
   as we will cover this properly in a later session.

   Notice how the makefile defines a variable named `CFLAGS`, containing
   options for the compiler. You'll be modifying this later.

   Using this makefile, you can compile the program from the terminal by
   entering `make task3`, or simply `make` on its own. You can remove
   the executable by entering `make clean`.

## Assertions

1. In a terminal window, compile the program by entering

       make

   Then run the program, supplying some suitable input on the command line:

       ./task3 1 2 3 4 5 6

   You should see that it sums the values correctly.

2. Try running the program with no command line arguments:

       ./task3

   The program halts due to a failed assertion. Study the output from the
   program carefully. Notice that it gives you details of the assertion that
   failed and where it occurs in the source code.

   In this case, the assertion `data != NULL` failed; in other words, `data`
   must have the value `NULL`. This happened on line 33, just inside the
   `sum_values()` function.

3. Now comment out line 53, so that `num_values` is not given the correct
   value. (Remember, you can do this by putting `//` at the start of the line.)

   Recompile by entering `make`, then run the program with a few integers as
   command line arguments. This time, the other assertion in `sum_values()`
   should fail.

   **Uncomment line 53 before proceeding further!**

4. Check the size of the executable by entering this command in the terminal
   window:

       wc -c task3

   number = 16256
   Make a note of the number you see. Then edit `Makefile` so that the
   `CFLAGS` variable includes a definition of the `NDEBUG` preprocessor
   symbol:

       CFLAGS = -DNDEBUG -Wall -Wextra -Werror

   Recompile the application and check its size again. You should see that it
   is slightly smaller, because the assertion code has been removed.

5. Run the program, without command line arguments. You should no longer
   see a failed assertion.

6. Comment out line 53 again, then recompile the program, and run it with
   some numbers as command line arguments. You won't see a failed assertion
   here, either (and the result of the calculation will be wrong!)

   Once again, uncomment line 53 before proceeding further.

## Conditional Logging

1. `task3.c` uses the logging macros `LOG_MSG()` and `LOG_FMT()` described
   on the slides. These are included from header file `logging.h`. Open
   this file and compare it with the code shown on the slides.

   Notice that there is some extra code in the file:

   ```c
   #ifndef _LOGGING_H_
   #define _LOGGING_H_
   ...
   #endif  // _LOGGING_H_
   ```

   This is known as an **include guard**. The preprocessor directive `#ifndef`
   means "if not defined". This code can be read as

   > "If the symbol `_LOGGING_H_` is not already defined, define it and
   > then process everything up to the matching `#endif` directive; if the
   > symbol *is* already defined, ignore everything up to the matching
   > `#endif`, because you've already seen it."

   An include guard like this prevents the contents of the header file from
   being processed more than once, should the file end up being included
   multiple times.

   Note: the include guard is not strictly needed here, because the header
   file contains only preprocessor macros, and the preprocessor allows you to
   redefine these without errors. You will encounter situations where include
   guards are absolutely necessary in later sessions.

2. You will have already seen that `LOG_MSG()` and `LOG_FMT()` don't generate
   any output as yet. This is because they have been defined in `task3.c` as
   empty, 'do nothing' macros.

   To change this, edit `Makefile` and alter the definition of `CFLAGS` to

       CFLAGS = -DVERBOSE -Wall -Wextra -Werror

   This will ensure that the `VERBOSE` preprocessor symbol is defined when
   the program is next compiled. With this symbol defined, `LOG_MSG()`
   and `LOG_FMT()` will be defined as calls to the `fprintf()` function.

3. Enter `make clean` to remove the previous version of the executable,
   followed by `make` to recreate it.

4. Run the application in the same ways that you did previously. You should
   now see detailed logging messages appear in the terminal.

5. You may have been wondering why these macros use `fprintf()` and the
   standard error channel `stderr`, instead of using `printf()`. The reason
   is flexibility. By default `stderr` and `stdout` are both connected to
   the terminal, but this doesn't have to be the case. We can redirect these
   channels independently, so that their output goes to files, or is piped
   into another tool, or is even discarded silently.

   For example, try this:

       ./task3 15 30 45 2> log.txt

   The `2>` redirects `stderr` to the file with the following name. As a
   result, regular program output still goes to the terminal but the logging
   messages end up in `log.txt` instead.

   If you want to discard the logging entirely, you can do

       ./task3 15 30 45 2> /dev/null

   If you want to redirect regular progam output but not the logging, use `>`
   instead of `2>`.

   If you want to redirect regular program output *and* logging to the
   same file, do this:

       ./task3 15 30 45 > output.txt 2>&1

6. Try adding more logging to `task3.c`, or changing the existing invocations
   of `LOG_MSG()` and `LOG_FMT()`.
