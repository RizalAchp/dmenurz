/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1; /* -b  option; if 0, dmenu appears at bottom     */
static int fuzzy  = 1; /* -F  option; if 0, dmenu doesn't use fuzzy matching  */
static int centered  = 0;   /* -c option; centers dmenu on screen */
static int min_width = 500; /* minimum width when centered */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char* fonts[] = {"monospace:size=10"};
/* -p  option; prompt to the left of input field */
static char* prompt = NULL;

#define THEME_NORD              0
#define THEME_DRACULA           1
#define THEME_DOOM_ONE          2
#define THEME_PALENIGHT         3
#define THEME_MONOKAI_PRO       4
#define THEME_GRUVBOX_DARK      5
#define THEME_OCEANIC_NEXT      6
#define THEME_SOLARIZED_DARK    7
#define THEME_TOMORROW_NIGHT    8
#define THEME_SOLARIZED_LIGHT   9

// 0 => nord
// 1 => dracula
// 2 => doom-one
// 3 => palenight
// 4 => monokai-pro
// 5 => gruvbox-dark
// 6 => oceanic-next
// 7 => solarized-dark
// 8 => tomorrow-night
// 9 => solarized-light
#define COLOR_IMPL
#define THEME THEME_GRUVBOX_DARK
#include "colors/include.h"

/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines = 0;
/* -h option; minimum height of a menu line */
static unsigned int lineheight     = 0;
static unsigned int min_lineheight = 8;
static unsigned int columns        = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static unsigned int border_width = 0;
