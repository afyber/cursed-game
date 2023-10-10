# Contributing

If you found a bug just make an issue in tab above and describe it as best you can, following the instructions in the issue template.

If you want to request a feature make an issue and begin its name with "Feature: ".

If you want to contribute code just make a fork of the repository and make your changes in a dev branch, then make a pull request into this repository. Make sure you have a descriptive title and description.

# Implementation Notes

Important stuff to remember.

* Be sure to check SDL_SCANCODE_KP_ENTER and SDL_SCANCODE_RETURN2 as well as SDL_SCANCODE_RETURN when checking to see if enter was pressed, some laptops use them instead


# Code Style

Some basic rules of code styling, they're not super important or anything, it's just how I like my code.

* Place a comment on the first line of a file with the format
```
// filename.ext, description
```

* Try to write code that "documents itself" by using clear function and variable names.

* Local variables, functions, classes, and most other names should use snake-case, e.g. `int thing_one;` and `void do_action();`.

* Global variables, including enum values, should be named using capital snake-case, e.g. `const int SCREEN_WIDTH = 100;`.

* Indentation should be four spaces per indent level.

* Operators should be speperated from their operands by spaces.

* The condition of an `if`, `while`, and `for` should be seperated from them by a space, and have a space placed after it.

* The `(` of a function should have no space between the function name and itself.

* The arguments of a function should have a space placed only after each comma.

* Statements requiring a block of code (an `if`, function definition, etc.) should always use curly braces to clearly show the code they refer to.

* When making a block of code with curly braces always place the inital `{` at the end of the first line, begin the code on the next line, and place the final `}` on a new line
```
if (this > that) {
    do_something();
    std::cout << "hello!";
}
```

* After the end of a block of code leave a blank line before the next statement (with the exception of `else` following an `if`)
```
void do_foo() {
    std::cout << "hello";
}

void do_bar();
```

* `else` statements should always be placed on the line following the `}` of the previous `if`
```
if (foo) {
    do_foo();
}
else if (bar) {
    do_bar();
}
```

* Function declarations should always have a blank line after them
```
void do_foo();

void do_bar();
```

* Header files should use this format
```
// name.hpp
#ifndef CURSED_NAME_HPP_
#define CURSED_NAME_HPP_

...

#endif
```