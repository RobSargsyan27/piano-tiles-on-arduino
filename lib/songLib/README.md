### Library Description
The `songLib` library contains functions playing songs.

#### Defined structs

 - `NOTE`: Defines object with `frequency` and `duration` fields.
 - `SONG`: Defines object with `name`, `length` and `notes` fields.

---
#### Defined function

 - `SONG* generateSong(char* name, uint16_t length)`: Generates songs with random notes and for random duration.
 - `void playNote(NOTE* note)`: Plays given `NOTE`.
 - `void playSong(SONG* song)`: Plays given `SONG`.
 - `void deleteSong(SONG* song)`: Deletes song from HEAP.