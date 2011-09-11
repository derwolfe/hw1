/*
 * Music DB ADTs external interface defined here
 */
const int MAX_INPUT_LENGTH = 100;
const int MAX_TRACKS_IN_PLAYLIST = 30;
const int MAX_TRACKS_IN_DB = 100;
const int MAX_PLAYLISTS_IN_DB = 10;

class Track 
{
 public:
  Track(const String268 &in_title,
	const String268 &in_artist,
	const String268 &in_album,
	const String268 &in_comment);

  bool matches(String268 &trac_title, String268 &track_artist);

  friend std::ostream& operator<<(std::ostream &os, Track &in_track);

  void print_title(std::ostream &os);

 private:
  String268 title;
  String268 artist;
  String268 album;
  String268 comment;
};

class Playlist 
{
 public:
  Playlist(const String268 &in_title);

  bool add_track(Track *in_track);
  bool matches(String268 &pl_title);
	
  friend std::ostream& operator<<(std::ostream &os, Playlist &in_playlist);

  void print_title(std::ostream &os);

 private:
  String268  title;
  Track     *tracks[MAX_TRACKS_IN_PLAYLIST];
  int        next_open_track_slot;
};

class Collection 
{
 public:
  Collection();

  bool      add_track(Track *in_track);
  bool      add_playlist(Playlist *in_playlist);

  Track    *find_track(String268 &track_title, 
		       String268 &track_artist);

  Playlist *find_playlist(String268 &pl_title);

  void      print_track_titles(std::ostream &os);
  void      print_playlist_titles(std::ostream &os);

  friend std::ostream& operator<<(std::ostream &os, Collection &in_collection);

 private:
  Track     *tracks[MAX_TRACKS_IN_DB];
  Playlist  *playlists[MAX_PLAYLISTS_IN_DB];
  int next_track_slot;
  int next_playlist_slot;
};

/*
 * Utility routine to process the music DB definition and command
 * files
 */
extern Collection *process_db_definition_file(ifstream &in_port);
extern void process_db_cmd_file(ifstream &in_port, 
				Collection in_collection,
				ostream &out_port);

