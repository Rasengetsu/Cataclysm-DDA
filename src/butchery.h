#pragma once

#include "character.h"
#include "map.h"

enum class butcher_type : int {
    BLEED,          // bleeding a corpse
    QUICK,          // quick butchery
    FULL,           // full workshop butchery
    FIELD_DRESS,    // field dressing a corpse
    SKIN,           // skinning a corpse
    QUARTER,        // quarter a corpse
    DISMEMBER,      // destroy a corpse
    DISSECT,        // dissect a corpse for CBMs
    NUM_TYPES       // always keep at the end, number of butchery types
};

struct butchery_data {
    item_location corpse;
    requirement_id req;
    butcher_type b_type;
    float req_speed_bonus;
    float progress;
    // in seconds
    int time_to_butcher;

    butchery_data( item_location &corpse, const butcher_type &b_type ) : corpse( corpse ),
        b_type( b_type ) {}
};

int butcher_time_to_cut( Character &you, const item &corpse_item, butcher_type action );

std::string butcher_progress_var( const butcher_type action );

double butcher_get_progress( const item &corpse_item, butcher_type action );

butcher_type get_butcher_type( player_activity *act );

bool set_up_butchery( player_activity &act, Character &you, butchery_data bd );

int roll_butchery_dissect( int skill_level, int dex, int tool_quality );

// Returns false if the calling function should abort
bool butchery_drops_harvest( butchery_data bt, Character &you );

void butchery_quarter( item *corpse_item, const Character &you );

void destroy_the_carcass( butchery_data bd, Character &you );

std::optional<butcher_type> butcher_submenu( const std::vector<map_stack::iterator> &corpses,
        int index = -1 );
