const int MAX_STRING268_LENGTH = 100;

class String268 
{
public:
  /*
   * Constructors for NULL initial content, initialization from a
   * C-string and initialization from another instance of a String268.
   */
  String268();
  String268(const char in_str[]);
  String268(const String268 &in_str);

  /*
   * Friend function that provides a signature for the << operator
   * that takes an instance of this class as its second argument.
   */
  friend std::ostream& operator<<(std::ostream &os, String268 &in_str);

  void        assign ( const String268 &in_str );
  int         compare_me ( const char *in_str );
  int         compare_me (  String268 &in_str );
  void        set_content ( const char *in_str );
  const char *char_ptr();

private:
  char content[MAX_STRING268_LENGTH+1];

};

