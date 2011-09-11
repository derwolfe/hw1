#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>

using namespace std;

#include "string268.h"

/*
 * String268.cpp content
 */
String268::String268()
{
  /*
   * initialize the content as an empty string
   */
  content[0] = '\0';
}

String268::String268(const char in_str[])
{
  int in_length;

  /*
   * Initialize the content frm the input string, but check to see if
   * it is too long.
   */
  in_length = strlen(in_str);
  if ( in_length >= MAX_STRING268_LENGTH ) {
    cout << "Error: creating a String268 with input too long" << endl;
    exit(1);
  }

  strcpy(content, in_str);
}

String268::String268(const String268 &in_str)
{
  strcpy(content, in_str.content);
}

std::ostream& operator<<(std::ostream &os, String268 &in_str)
{
  os << in_str.content;
  return os;
}

/*
 * The compare functions compare an input C-string or String268 to the
 * contents of this instance.
 *
 * Return 0 for equal to content, -1 for less than in_str and 1 for
 * greater than in_str.
 */
int String268::compare_me ( const char *in_str  )
{
  int retval;

  retval = strcmp(in_str, content);

  if ( retval == 0) {
    return 0;
  } else if ( retval < 0 ) {
    return -1;
  } else {
    return 1;
  }
}

int String268::compare_me ( String268 &in_str  )
{
  int retval;

  retval = strcmp(in_str.char_ptr(), content);

  if ( retval == 0) {
    return 0;
  } else if ( retval < 0 ) {
    return -1;
  } else {
    return 1;
  }
}


/*
 * Assign the content of the input parameter instance of String268 to
 * the cntent of this instance. Similar to "A = B;" if A and B are
 * instances of the class, but written "A.assign(B);".
 */
void String268::assign ( const String268 &in_str )
{
  if ( this == &in_str) {
    return;
  } else {
    strcpy(content, in_str.content);
  }
}

/*
 * Set of the content of this instance from a C-string.
 */
void String268::set_content ( const char *in_str  )
{
  int len;
  len = strlen(in_str);

  if ( len >= MAX_STRING268_LENGTH ) {
    cout << "ERROR: input C-string too long for String268" << endl;
    exit(-1);
  }

  strcpy(content, in_str);
}

/*
 * Return a charater pointer for the contents so it can be used as
 * input to C-string utility routines.
 */
const char * String268::char_ptr()
{
  return &content[0];
}


