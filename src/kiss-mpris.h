#define MAX_OUTPUT_LENGTH 1024

#include <stdbool.h>
#include <stdint.h>

typedef struct mpris_metadata {
    uint64_t length; // mpris specific
    unsigned short track_number;
    unsigned short bitrate;
    unsigned short disc_number;
    char album_artist[MAX_OUTPUT_LENGTH];
    char composer[MAX_OUTPUT_LENGTH];
    char genre[MAX_OUTPUT_LENGTH];
    char artist[MAX_OUTPUT_LENGTH];
    char comment[MAX_OUTPUT_LENGTH];
    char track_id[MAX_OUTPUT_LENGTH];
    char album[MAX_OUTPUT_LENGTH];
    char content_created[MAX_OUTPUT_LENGTH];
    char title[MAX_OUTPUT_LENGTH];
    char url[MAX_OUTPUT_LENGTH];
    char art_url[MAX_OUTPUT_LENGTH]; //mpris specific

} mpris_metadata;

typedef struct mpris_properties {
    double volume;
    uint64_t position;
    bool can_control;
    bool can_go_next;
    bool can_go_previous;
    bool can_play;
    bool can_pause;
    bool can_seek;
    bool shuffle;
    char player_name[MAX_OUTPUT_LENGTH];
    char loop_status[MAX_OUTPUT_LENGTH];
    char playback_status[MAX_OUTPUT_LENGTH];
    mpris_metadata metadata;
} mpris_properties;

typedef enum mpris_player_status {
    MPRIS_PLAYER_MUST_BE_PLAYING,
    MPRIS_PLAYER_ANY_PLAYING,
    MPRIS_PLAYER_ANY
} mpris_player_status;

typedef struct kiss_mpris_options {
    // char* list of names
    char **player_names;
    int player_count;

    mpris_player_status status;
} kiss_mpris_options;

#undef MAX_OUTPUT_LENGTH

extern mpris_properties get_mpris_player_status(kiss_mpris_options *options);

