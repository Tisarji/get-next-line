# Get Next Line

This project is about programming a function that allows you to read content line by line. This is done by returning a line read from a file descriptor.

## Function Description

The primary function in this project is `get_next_line`, which reads from a file descriptor (`fd`) and returns one line or `NULL`.

**Return Value:**
- `char *`: The string containing a line read by the function.
- `(null)`: Either an error occurred or reached EOF (End Of File).

### How it Works

This project includes several helper functions that the `get_next_line` function utilizes:

- `strjoin`: Function to concatenate strings.
- `strlen`: Function to find the length of a string.
- `strchr`: Function to find the first occurrence of a character in a string.
- `strdup`: Function to duplicate a string.
- `substr`: Function to extract a substring from a string.

### My result in Get Next Line
<img width="1075" alt="Screenshot 2566-10-15 at 01 24 41" src="https://github.com/Tisarji/get-next-line/assets/48820052/abfecdae-c3b8-497c-b32f-ee0b7b3c5fa9">

