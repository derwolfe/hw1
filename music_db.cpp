#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>

using namespace std;

#include "string268.h"
#include "music_db.h"

/*
 * This section defines the methods for the Track Class
 */
Track::Track(const String268 &in_title,
	     const String268 &in_artist,
	     const String268 &in_album,
	     const String268 &in_comment)
{
  title.assign(in_title);
  artist.assign(in_artist);
  album.assign(in_album);
  comment.assign(in_comment);
}

/*
 * Return true if both the input strings match the title and artist of
 * this object. Return False otherwise.
 */
bool Track::matches(String268 &in_title, String268 &in_artist)
{
    if (( title.compare_me( in_title ) == 0 ) && 
        ( artist.compare_me( in_artist ) == 0 )) {
        return true; 
    return false;
    }    
}
void Track::print_title(std::ostream &os)
{
    os << title << endl;
}
// overloaded the << operator to print all of the class definitions
// of Track
std::ostream& operator<<(std::ostream &os, Track &in_track)
{
    os << "  Title:     " << in_track.title << endl; 
    os << "  Artist:    " << in_track.artist << endl;
    os << "  Album:     " << in_track.album << endl;
    os << "  Comment:   " << in_track.comment << endl;
    os << endl;
    return os;
}

/****************************************************************/

/*
 * This section defines the methods for the Playlist Class
 */
Playlist::Playlist(const String268 &in_title)
// this method constructs the playlist and assigns it a title
// assign the title and initialize the playlist with tracks
// also allocates the playlist space
{
    title.assign(in_title); 
//    for (int i = 0; i < MAX_TRACKS_IN_PLAYLIST; i++ ) {
//       tracks[i] = (Track *)0;   
//    }
    next_open_track_slot = 0;
}

/*
 * Add a track to this playlist. Return true if successful, and false
 * if not
 */
bool Playlist::add_track(Track *in_track)
// Checks to see if playlist is full, if not it adds in_track to
// tracks in the currently set next available slot. The 
// next_open_track_slot is then advanced and true is returned.

{

    if (in_track == NULL)
        return false;

    if ( next_open_track_slot < MAX_TRACKS_IN_PLAYLIST ) {
        tracks[next_open_track_slot] = in_track;
        next_open_track_slot++;    
        return true;
    }  

    return false;

}
/*
 * See if the input title matches the title of this playlist. Return
 * true if so, false otherwise.
 */
bool Playlist::matches(String268 &in_title)
{
    if ( title.compare_me(in_title) == 0 ) {    
        return true;
    }
    return false;
}

void Playlist::print_title(std::ostream &os)
{
    os << title << endl;
}

std::ostream& operator<<(std::ostream &os, Playlist &in_playlist)
{
    os << "Title:   " << in_playlist.title << endl;
    return os;
}

/****************************************************************/

/*
 * This section defines the methods for the Collection Class
 */

Collection::Collection()
{
    for ( int i = 0; i < MAX_TRACKS_IN_DB; i++ ) {
      tracks[i] = (Track *)0;
    }
    next_track_slot = 0;

    for ( int i = 0; i < MAX_PLAYLISTS_IN_DB; i++ ) {
      playlists[i] = (Playlist *)0;
    }
    next_playlist_slot = 0;
}

/*
 * Add a track. Return true if successful, false otherwise.
 */
bool Collection::add_track(Track *in_track)
{
    if ( in_track == NULL ) {
        return false;
    }

    if ( next_track_slot < MAX_TRACKS_IN_DB ) {
        tracks[next_track_slot] = in_track;
        next_track_slot++;
        return true;
    } 

    return false;

}

bool Collection::add_playlist(Playlist *in_playlist)
{
    if ( in_playlist == NULL ) {
        return false;
    }
    if ( next_playlist_slot < MAX_PLAYLISTS_IN_DB ) {
        playlists[next_playlist_slot] = in_playlist;
        next_playlist_slot++;
        return true;
    } 
    return false;

}

/*
 * Find a track that matches on both title and artist strings. Return
 * a pointer to the Track instance if found, a NULL pointer otherwise.
 */
Track *Collection::find_track(String268 &track_title, 
				 String268 &track_artist)
{
   /* for track in Collection
   *   if track.matches(track_title, track_artist):
   *       return track
   *   else:
   *       return (track *)0
   *       
   * return (Track *)0;
   */ 
    int i = 0;
    while ( i < MAX_TRACKS_IN_DB ) {
        if (tracks[i]->matches( track_title, track_artist )) {
            return tracks[i];
        i++;
        }
    return (Track *)0;
    }
}


/*
 * Find a playlist by name. Return a pointer to the instance if found,
 * a NULL pointer otherwise.
 */
Playlist *Collection::find_playlist(String268 &pl_title)
{
  //similar to above, just with different vars//
    int i = 0;
    while ( i < MAX_PLAYLISTS_IN_DB ) {
       if ( playlists[i]->matches( pl_title )) {
            return playlists[i];
       }
       i++;
    }
    return (Playlist*) 0;
}

void Collection::print_track_titles(std::ostream &os)
/* Cycle through the set of tracks, provide output stream 
 * the title
 */ 
{
    for ( int i = 0; i < MAX_TRACKS_IN_DB; i++ ) {
        tracks[i]->print_title(os);
    }
}

void Collection::print_playlist_titles(std::ostream &os)
/* Cycle through the set of playlists, provide output 
 * stream with the title
 */ 
{
    for ( int i = 0; i < MAX_PLAYLISTS_IN_DB; i++ ) {
        playlists[i]->print_title(os);
    }
}

std::ostream& operator<<(std::ostream &os, Collection &in_collection)
{
  os << "**********************************" << endl;
  os << "*      Collection as a Whole     *" << endl;
  os << "**********************************" << endl;

  os << endl;
  os << "              *******************" << endl;
  os << "              *     Tracks      *" << endl;
  os << "              *******************" << endl;
    in_collection.print_track_titles(os); 
  os << endl;

  os << "              *******************" << endl;
  os << "              *    Playlists    *" << endl;
  os << "              *******************" << endl;
    in_collection.print_playlist_titles(os);
  return os;
}

/**********************************************************************/

/****************************/
/***   Utility Routines   ***/
/****************************/

/*
 * Define a set of ID values for the Music DB commands and their
 * argument labels
 *
 * We create defined constants and constant integers for the command
 * vlaues so we can use the integers as return vlaues,a nd the defined
 * constants as labels in a switch statement.
 */
const int CMD_ADD_TRACK        = 1;
const int CMD_ADD_PLAYLIST     = 2;
const int CMD_PRINT_TRACK      = 3;
const int CMD_LIST_TRACKS      = 4;
const int CMD_PRINT_PLAYLIST   = 5;
const int CMD_LIST_PLAYLISTS   = 6;
const int CMD_PRINT_COLLECTION = 7;

const int ARG_TITLE        = 10;
const int ARG_ARTIST       = 11;
const int ARG_ALBUM        = 12;
const int ARG_COMMENT      = 13;
const int ARG_PL_TITLE     = 14;

/*
 * Examine the input line to see what cmmand is being
 * specified. Return the command code if found, or -1 if not.
 */
int identify_next_command(const char cmd_line[])
{

  if ( strcmp(cmd_line, "add_track") == 0 ) {
    return CMD_ADD_TRACK;
  }

  if ( strcmp(cmd_line, "add_playlist") == 0 ) {
    return CMD_ADD_PLAYLIST;
  }

  if ( strcmp(cmd_line, "print_track") == 0 ) {
    return CMD_PRINT_TRACK;
  }

  if ( strcmp(cmd_line, "list_tracks") == 0 ) {
    return CMD_LIST_TRACKS;
  }

  if ( strcmp(cmd_line, "print_playlist") == 0 ) {
    return CMD_PRINT_PLAYLIST;
  }

  if ( strcmp(cmd_line, "list_playlists") == 0 ) {
    return CMD_LIST_PLAYLISTS;
  }

  if ( strcmp(cmd_line, "print_collection") == 0 ) {
    return CMD_PRINT_COLLECTION;
  }

  return -1;
}

/*
 * Parse a DB defnition of DB command line of the form:
 *      field:value
 *
 * Check to see that the field was as expected, and then return the
 * value in the target parameter
 */
void parse_field_line(const char *field_label, char input_line[], String268 &target)
{
  char *cp1;
  char *cp2;

  cp1 = strchr(input_line, ':');
  cp2 = cp1 + 1;
  *cp1 = '\0';
  if ( !strcmp(cp2, field_label) ) {
    cout << "ERROR: input arguments out of sequence" << endl;
    exit(-1);
  }
  target.set_content(cp2);
}

Track *process_add_track(ifstream &in_port)
{
    Track *new_track;
    char   input_line[MAX_INPUT_LENGTH];

    String268 title;
    String268 artist;
    String268 album;
    String268 comment;

     /*
     * Read the title, artist, album, and comment lines from the file in
     * that order
     */
    /* the first line received will be for the title, then artist etc.
    * line is automatically advanced
    * the variables are set, then placed in the new Track object 
    */
    in_port.getline( input_line, MAX_INPUT_LENGTH );     
    parse_field_line( "title", input_line, title );
    in_port.getline( input_line, MAX_INPUT_LENGTH ); 
    parse_field_line( "artist", input_line, artist );
    in_port.getline( input_line, MAX_INPUT_LENGTH ); 
    parse_field_line( "album", input_line, album );
    in_port.getline( input_line, MAX_INPUT_LENGTH ); 
    parse_field_line( "comment", input_line, comment ); 
    /*
    * Now construct an instance of Track initializing it with the
    * values just read fromtfileds he file
    */
    new_track = new Track( title, artist, album, comment );
    return new_track;
}

Playlist *process_add_playlist(ifstream &in_port, Collection &collection)
{
    Playlist *new_playlist;
    Track    *track_ptr;
    char      input_line[MAX_INPUT_LENGTH];

    String268 pl_title;
    String268 track_title;
    String268 track_artist;

  /*
   * Read the title of the playlist and then dynamically allocate an
   * instance of Playlist providing the title just read
   */
    in_port.getline( input_line, MAX_INPUT_LENGTH );
    parse_field_line( "title", input_line, pl_title );
    // check if title is empty, if not instantiate w/ pl_title 
    if ( !pl_title.compare_me("") ) {
        new_playlist = new Playlist( pl_title );
    }
  /*
   * Now read pairs of track titles and artists that are elements of
   * the playlist. Look them up in the tracks defined in the
   * collection so far, and then add a pointer to the Track object in
   * the next playlist slot.
   *
   * Terminate the loop when we hit a blank line by executing the
   * break command.
   */

    while ( true ) {

        in_port.getline( input_line, MAX_INPUT_LENGTH );
        if (!strlen(input_line)) {
        /*
        * Blank line terminates the list of tracks specified for a play
        * list
        */
            break;
        }
        /* Implied ELSE: parse the input, read track info into track_title and 
         * track_artist
         */
        parse_field_line( "title", input_line, track_title ); 
        in_port.getline( input_line, MAX_INPUT_LENGTH );
        parse_field_line( "artist", input_line, track_artist );

       /*
        * Find the track in the collection by title and artist pair read
        * in as part of the playlist definition using the find_track
        * method in the Collection Class.
         */
        track_ptr = collection.find_track( track_title, track_artist );
        /*
        * Add the pointer to the track instance to the playlist
        */  
        new_playlist->add_track(track_ptr); 
    }
     /*
     * return the constructed playlist
     */
    return new_playlist;
}

/*
 * Process the set of commands defining additions to the DB
 */
Collection *process_db_definition_file(ifstream &in_port)
{
  const int  MAX_INPUT_LENGTH = 100;
  char       input_line[MAX_INPUT_LENGTH];

  int        cmd_id;

  Track     *new_track_p;
  Playlist  *new_playlist_p;

  Collection *collection_p;

  collection_p = new Collection;

  while ( !in_port.eof() ) {
    in_port.getline(input_line, MAX_INPUT_LENGTH);

    /*
     * Skip blank lines and those starting with a # in column 0 which
     * we declare to be comments
     */
    if ( input_line[0] == '\0' ) {
      continue;
    }

    if ( input_line[0] == '#' ) {
      continue;
    }

    /*
     * Find out what command is next and then call the appropriate
     * routine to process the input for that command
     */
    cmd_id = identify_next_command(input_line);
    switch ( cmd_id ) {
    case CMD_ADD_TRACK:
      new_track_p = process_add_track(in_port);
      if ( !(*collection_p).add_track(new_track_p) ) {
	cout << "Error: failure during reading a track definition" << endl;
	return (Collection *)0;
      }
      break;

    case CMD_ADD_PLAYLIST:
      new_playlist_p = process_add_playlist(in_port, *collection_p);
      if ( !(*collection_p).add_playlist(new_playlist_p) ) {
	cout << "Error: failure during reading a playlist definition" << endl;
	return (Collection *)0;
      }
      break;

    default:
      cout << "ERROR: This should never happen as a proper ID should always be returned" << endl;
      break;
    }
  }
  return collection_p;
}

/*
 *  Process the file specifying commands on the DB built
 */
void process_db_cmd_file(ifstream &in_port, Collection in_collection, 
			 ostream &out_port )
{
  const int  MAX_INPUT_LENGTH = 100;
  char       input_line[MAX_INPUT_LENGTH];

  int        cmd_id;

  String268  title_value;
  String268  artist_value;

  Track     *track_p;
  Playlist  *playlist_p;

  while ( !in_port.eof() ) {
    in_port.getline(input_line, MAX_INPUT_LENGTH);

    /*
     * Skip blank lines and those starting with a # in column 0 which
     * we declare to be comments
     */
    if ( input_line[0] == '\0' ) {
      continue;
    }

    if ( input_line[0] == '#' ) {
      continue;
    }

    /*
     * Find out what command is next and then call the appropriate
     * routine to process the input for that command
     */
    cmd_id = identify_next_command(input_line);
    switch ( cmd_id ) {
    case CMD_PRINT_TRACK:
      /*
       * Get the title and artist field values and then try to find
       * the track in the collection.
       */
      in_port.getline( input_line, MAX_INPUT_LENGTH);  
      parse_field_line( "title", input_line, title_value );
      in_port.getline( input_line, MAX_INPUT_LENGTH );
      parse_field_line( "artist", input_line, artist_value );
      
      track_p = in_collection.find_track( title_value, artist_value );
        out_port << track_p << endl;
      if ( track_p == (Track *)0 ) {
	    cout << "Error: failure finding a track" << endl;
	    cout <<  "Title:  " << title_value  << endl;
	    cout <<  "Artist: " << artist_value << endl;
    	exit(1);
      }

      out_port << "******************" << endl;
      out_port << "**  Print Track **" << endl;
      out_port << "******************" << endl;
      out_port << *track_p << endl;
      break;
    /* currently implemented using outport as the output stream
     * this may be incorrect as several functions are sending derefenced 
     * objects (i.e. their values) to the output stream.
     */
    case CMD_PRINT_PLAYLIST:
      /*
       * Process the title field line then look for aplaylist with
       * that title.
       */
     /* if playlist matches 
      *     return pointer to paylist
      *     else return null playlist point
      */
      playlist_p = in_collection.find_playlist( title_value );
      if ( playlist_p == (Playlist *)0 ) {
	    cout << "Error: failure finding a playlist" << endl;
    	cout <<  "Title:  " << title_value  << endl;
	    exit(1);
      }

      out_port << "*********************" << endl;
      out_port << "**  Print Playlist **" << endl;
      out_port << "*********************" << endl;
      out_port << *playlist_p << endl;
      break;

    case CMD_LIST_TRACKS:
      out_port << "*************************" << endl;
      out_port << "* List All Track Titles *" << endl;
      out_port << "**************************" << endl;
      //out_port << in_collection.tracks << endl;
        in_collection.print_track_titles( out_port );
      out_port << endl;
      break;

    case CMD_LIST_PLAYLISTS:
      out_port << "****************************" << endl;
      out_port << "* List All Playlist Titles *" << endl;
      out_port << "****************************" << endl;
        in_collection.print_playlist_titles( out_port );
      out_port << endl;
      break;

    case CMD_PRINT_COLLECTION:
      out_port << "**************************" << endl;
      out_port << "* Print Whole Collection *" << endl;
      out_port << "**************************" << endl;      
      out_port << in_collection << endl;
      out_port << endl;
      break;

    default:
      cout << "ERROR: This should never happen as a proper ID should always be returned" << endl;
      exit(1);
      break;
    }
  }
}


