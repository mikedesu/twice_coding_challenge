# Twice Coding Challenge

From the email:

> Can you create a program to solve a word jumble? (More info here.) The program should accept a string as input, and then return a list of words that can be created using the submitted letters. For example, on the input "dog", the program should return a set of words including "god", "do", and "go".
> 
> Please implement the program in a language of your choice, but refrain from using any combinatorics helper modules or imports (e.g. itertools in Python). In order to verify your words, just download an English word list (here are a few). Then upload your program to GitHub or Gist, and send it back!

The dictionary that I am using: [http://www.mieliestronk.com/corncob_lowercase.txt](http://www.mieliestronk.com/corncob_lowercase.txt)

<hr/>

# Explanation of my solution

I could have used a more "powerful" / higher-level language, but I like C, and I wanted to challenge myself.

I ran into a number of issues in just reading in the word list (efficient file i/o is hard), so I decided to try implementing an AVL tree. This will be later used in another small project that I am working on, so it is win-win.

There are two issues that I can think of that need to be watched out for:

1. If your dictionary has words with more than 32 characters, you should change the define in avl_node.h:

```
#define MAX_STRING_LENGTH 32
```

Same goes for the words that you might permute in argv[2]. In main.c, change the define to reflect possible max string length:

```
#define BUFFER_SIZE 32
```

2. This particular input dictionary has some annoying control characters at the end of each word in addition to a newline character, which is why I do the following in main.c:47

```
buffer[len-1] = '\0';
buffer[len-2] = '\0';
```

Keep this in mind when feeding it dictionary files. You may need to adjust where null characters are set in order for everything to work smoothly.

<hr/>

# To build

```
./build.sh
```

**Note**: you need *clang* to do this by default. If you don't have *clang*, you can change the variable, *CC*, in the *Makefile* to read *gcc*.

```
CC=gcc
```

<hr/>

# Usage

```
usage: ./main <input_dictionary_file> <input_word>
```

<hr/>

# Sample output

```
Mike ~/src/twice_coding_challenge $ ./main corncob_lowercase.txt dog
dog
do
god
go
```

