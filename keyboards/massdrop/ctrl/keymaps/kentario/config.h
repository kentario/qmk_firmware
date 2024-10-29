#pragma once

// Double tapping left shift turns on caps word.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Time in milliseconds before a oneshot key is released.
#define ONESHOT_TIMEOUT 1000

#define LEADER_PER_KEY_TIMING
// Each time a key of the sequence is pressed, an additional 250 milliseconds are given to complete the sequence.
#define LEADER_TIMEOUT 250

// All combos are done as if the current layer is the Colemak Mod-DH layer.
#define COMBO_ONLY_FROM_LAYER 0

// Time in milliseconds in which the key needs to be repeated in order to be detected as a multi tap.
#define TAPPING_TERM 200
