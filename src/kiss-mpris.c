#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "sdbus.h"

mpris_properties get_mpris_player_status(kiss_mpris_options *options) {
    // initialise the errors
    DBusError err = {0};
    dbus_error_init(&err);

    // connect to the system bus and check for errors
    DBusConnection *conn = dbus_bus_get_private(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "DBus connection error(%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (NULL == conn) {
        fprintf(stderr, "D-Bus connection failed");
    }

    mpris_player players[MAX_PLAYERS] = {0};
    int found = load_players(conn, players);

    mpris_properties returned_data = { 0 };

    for (int i = 0; i < found; i++) {
        bool skip = true;
        bool playing = false;
        mpris_player player = players[i];
        load_mpris_properties(conn, player.namespace, &player.properties);

        if (strncmp(player.properties.playback_status,
                    MPRIS_METADATA_VALUE_PLAYING, 8) == 0) {
            switch(options->status) {
                case MPRIS_PLAYER_ANY_PLAYING:
                case MPRIS_PLAYER_ANY:
                    skip = false;
                    break;
                default:
                    playing = true;
                    break;
            }
        }

        if ((options->status == MPRIS_PLAYER_ANY) &&
            (strncmp(player.properties.playback_status,
                     MPRIS_METADATA_VALUE_PAUSED, 7) == 0 ||
            strncmp(player.properties.playback_status,
                MPRIS_METADATA_VALUE_STOPPED, 8) == 0)) {
            skip = false;
        }

        // Find player by name routine
        for (int i = 0; i < options->player_count; i++) {
            char *player_name = options->player_names[i];
            if (NULL != player_name) {
                size_t name_len = strlen(player_name);
                size_t prop_name_len = strlen(player.properties.player_name);
                size_t prop_ns_len = strlen(player.namespace);
                if (prop_name_len < name_len) {
                    prop_name_len = name_len ;
                }
                if (prop_ns_len < name_len) {
                    prop_ns_len = name_len;
                }
                if (strncmp(player.properties.player_name, player_name, prop_name_len) == 0 ||
                   strncmp(player.namespace, player_name, prop_ns_len) == 0) {
                    if((options->status == MPRIS_PLAYER_MUST_BE_PLAYING) &&
                            !playing) {
                        // noop because nik is lazy
                    } else skip = false;
                }
            }
        }

        if(skip)
            continue;

        returned_data = player.properties;
    }

    if (NULL != conn) {
        dbus_connection_close(conn);
        dbus_connection_unref(conn);
    }

    return returned_data;
}

