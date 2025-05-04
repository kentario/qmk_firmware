/* Copyright 2023 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT

// Oneshot keys don't time out.
#define ONESHOT_TIMEOUT 0

// Double tab left shift to turn on caps word.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// Caps word has no idle timeout.
#define CAPS_WORD_IDLE_TIMEOUT 0

// Time in milliseconds in which the key needs to be repeated in order to be detected as a multi tap.
#define TAPPING_TERM 200
