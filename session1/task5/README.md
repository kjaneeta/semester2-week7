# Task 5

This task explores the basic features of the GNU Debugger, GDB.

**Note**: we have provided a makefile to make it easy to compile the programs
for this task. **You do not need to understand how this works!** We will cover
Makefiles in a later session.

## `vars.c`

This program creates some variables, using a mixture of static (stack-based)
and dynamic (heap-based) memory allocation.

1. Compile the program in the terminal using

       make vars

   You can see the compiler command echoed in the terminal. Note the use
   of the `-g` option, allowing the program to be debugged.

   Run the program in the terminal, with

       ./vars

2. Now load the program into GDB:

       gdb vars

   List some of the source code by entering the command `list` a couple of
   times. (You can abbreviate `list` to `l`, if you like.)

3. Create a breakpoint at line 10, like so:

       break 10

   You can abbreviate `break` to `b` if you prefer.

4. Run the program with `run` (or `r`, if you prefer). Execution should
   pause at line 10.

5. Print out the current values of the program's local variables with

       p i
       p j
       p static_array
       p dyn_array

   Notice how the entire contents of `static_array` are displayed. You may
   find that some of the values in the array are zero and others are not.
   Stack-based arrays are not initialized by default.

   Depending on where you try this, you may find that `dyn_array` displays
   as `0x0` (NULL), which is not a valid memory address for the program.
   If you see a non-null value for `dyn_array` it still doesn't represent a
   memory address that we should use. We need to either make `dyn_array`
   point to some existing storage or allocate new storage for it.

6. Enter this command:

       until 14

   This will resume execution until we reach line 14 - i.e., after the `for`
   loop that initializes `static_array`. Note that this command does not
   create a new breakpoint.

   Press the up arrow key a couple of times, to bring back the command that
   prints `static_array`, then press Enter. You should now see the value
   0.5 appearing in every element of the array.

7. Create a new breakpoint on line 20, with `b 20`. Check on the status of
   the breakpoints using `info breakpoints` or `info b` for short.

   Then resume execution by entering `continue` (or `c`, if you prefer).
   Execution should pause at line 20.

   Press the up arrow key a few times, to bring back the command that prints
   `dyn_array`. This pointer should now have a different value, because it
   points to the memory allocated by `malloc()`.

8. Try the following commands:

   ```
   p dyn_array + 1
   p dyn_array + 2
   p *(dyn_array + 1)
   p *(dyn_array + 2)
   ```

   You can see that the `p` command prints *expressions*, rather than being
   limited to simple variables. The first two expressions produce pointers to
   the second and third elements of `dyn_array`, respectively. You can see
   that the displayed memory address goes up by 4 each time - the size of an
   `int`.

   The third and fourth commands dereference those two pointer expressions
   that represent the second and third elements, showing us the values stored
   at those locations.

9. Enter `c` to resume executing the program. It should run to completion.
   Then enter `quit` or `q` to exit the debugger.

## `factorial.c`

This program computes the factorial of the integer provided on the command
line, but it has some problems.

1. Compile the program in the terminal with

       make factorial

2. Run the program in the terminal, first without a command line argument,
   then using `5` as the sole argument:

       ./factorial
       ./factorial 5

   The first of these should print a usage message; the second should
   trigger a segmentation fault.

3. Load the program into GDB:

       gdb factorial

   Then start the program with a command line argument of 5:

       start 5

   The program should pause at a temporary breakpoint, just inside `main()`.

4. Print out the values of `argc` and `argv`:

       p argc
       p argv

   The first of these should print 2, the second should print a memory address.

   Then print out the values of two strings held in `argv`:

       p argv[0]
       p argv[1]

       $3 = 0x7fffffffd3ff "/workspaces/semester2-week7/session1/task5/factorial"
   (gdb) p argv[1]
   $4 = 0x7fffffffd434 "5"
   (gdb) 

5. Use `next` or `n` twice, to move past the code that parses the command
   line. Print the variable `value`, to check that it is equal to 5 as
   expected.

   You are now on the statement that calls `factorial()`, although this hasn't
   executed yet. Use `step` or `s` to call the function and step inside it.

   GDB will print a message to tell you that the call happened. This message
   will include details of the arguments passed to the function:

       factorial (n=5) at factorial.c:6

(gdb) s
factorial (n=5) at factorial.c:6
6           return n * factorial(n - 1);



6. Use `s` three more times to continue invoking `factorial()` recursively.
   Notice how the value of parameter `n` descreases by 1 each time.

   Then enter `backtrace` or `bt` to view the call stack. This will show
   clearly the details of the recursion.

7. Recurse further by using `s` three more times. At this point `n` should
   have a negative value. It should now be clear that there is nothing
   to stop recursion from continuing until all available stack space has
   been exhausted.

8. Note that we could have learned about the issue without needing to run
   the debugger. To see how, edit `Makefile` and change the value of variable
   `CFLAGS` to be this:

       CFLAGS = -g -Wall -Wextra -Werror

   Remove the old executable with `make clean`, then attempt to rebuild the
   executable with `make factorial`. You should now see an error message
   informing you of the infinite recursion in `factorial()`.

9. Add a base case to the `factorial()` function that prevents the infinite
   recursion from happening. Verify that this has fixed the issue.

   Is all well with `factorial.c` now? Investigate its behaviour further by
   running it with different integer arguments. You should be able to
   identify (and fix) another bug...

   (Hint: what is the limitation that arises from the use of a `long int`
   variable?)
