// library goes above
#include "sstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kiss-mpris.h>

#define INFO_DEFAULT_STATUS "%track_name - %album_name - %artist_name"
#define INFO_FULL_STATUS    "Player name:\t" INFO_PLAYER_NAME "\n" \
"Play status:\t" INFO_PLAYBACK_STATUS "\n" \
"Track:\t\t" INFO_TRACK_NAME "\n" \
"Artist:\t\t" INFO_ARTIST_NAME "\n" \
"Album:\t\t" INFO_ALBUM_NAME "\n" \
"Album Artist:\t" INFO_ALBUM_ARTIST "\n" \
"Art URL:\t" INFO_ART_URL "\n" \
"Track:\t\t" INFO_TRACK_NUMBER "\n" \
"Length:\t\t" INFO_TRACK_LENGTH "\n" \
"Volume:\t\t" INFO_VOLUME "\n" \
"Loop status:\t" INFO_LOOP_STATUS "\n" \
"Shuffle:\t" INFO_SHUFFLE_MODE "\n" \
"Position:\t" INFO_POSITION "\n" \
"Bitrate:\t" INFO_BITRATE "\n" \
"Comment:\t" INFO_COMMENT \
""

#define INFO_PLAYER_NAME     "%player_name"
#define INFO_TRACK_NAME      "%track_name"
#define INFO_TRACK_NUMBER    "%track_number"
#define INFO_TRACK_LENGTH    "%track_length"
#define INFO_ARTIST_NAME     "%artist_name"
#define INFO_ALBUM_NAME      "%album_name"
#define INFO_ALBUM_ARTIST    "%album_artist"
#define INFO_ART_URL         "%art_url"
#define INFO_BITRATE         "%bitrate"
#define INFO_COMMENT         "%comment"

#define INFO_PLAYBACK_STATUS "%play_status"
#define INFO_SHUFFLE_MODE    "%shuffle"
#define INFO_VOLUME          "%volume"
#define INFO_LOOP_STATUS     "%loop_status"
#define INFO_POSITION        "%position"

#define INFO_FULL            "%full"

#define TRUE_LABEL      "true"
#define FALSE_LABEL     "false"

#define PLAYER_ACTIVE    "active"
#define PLAYER_INACTIVE  "inactive"

void print_mpris_info(mpris_properties *props, const char* format)
{
    const char* info_full = INFO_FULL_STATUS;
    const char* shuffle_label = (props->shuffle ? TRUE_LABEL : FALSE_LABEL);
    char volume_label[5];
    snprintf(volume_label, 5, "%.2f", props->volume);
    char pos_label[11];
    snprintf(pos_label, 11, "%.2lfs", (props->position / 1000000.0));
    char track_number_label[6];
    snprintf(track_number_label, 6, "%d", props->metadata.track_number);
    char bitrate_label[6];
    snprintf(bitrate_label, 6, "%d", props->metadata.bitrate);
    char length_label[15];
    snprintf(length_label, 15, "%.2lfs", (props->metadata.length / 1000000.0));

    char output[10240];
    memcpy(output, format, strlen(format) + 1);

    str_replace(output, "\\n", "\n");
    str_replace(output, "\\t", "\t");

    str_replace(output, INFO_FULL, info_full);
    str_replace(output, INFO_PLAYER_NAME, props->player_name);
    str_replace(output, INFO_SHUFFLE_MODE, shuffle_label);
    str_replace(output, INFO_PLAYBACK_STATUS, props->playback_status);
    str_replace(output, INFO_VOLUME, volume_label);
    str_replace(output, INFO_LOOP_STATUS, props->loop_status);
    str_replace(output, INFO_POSITION, pos_label);
    str_replace(output, INFO_TRACK_NAME, props->metadata.title);
    str_replace(output, INFO_ARTIST_NAME, props->metadata.artist);
    str_replace(output, INFO_ALBUM_ARTIST, props->metadata.album_artist);
    str_replace(output, INFO_ALBUM_NAME, props->metadata.album);
    str_replace(output, INFO_TRACK_LENGTH, length_label);
    str_replace(output, INFO_TRACK_NUMBER, track_number_label);
    str_replace(output, INFO_BITRATE, bitrate_label);
    str_replace(output, INFO_COMMENT, props->metadata.comment);
    str_replace(output, INFO_ART_URL, props->metadata.art_url);

    fprintf(stdout, "%s\n", output);
}

int main() {
    kiss_mpris_options options;
    options.player_count = 1;
    options.player_names = malloc(sizeof(char*));
    options.player_names[0] = "Spotify";
    options.status = MPRIS_PLAYER_MUST_BE_PLAYING;

    mpris_properties properties = get_mpris_player_status(&options);

    print_mpris_info(&properties, INFO_FULL_STATUS);
    free(options.player_names);
}

