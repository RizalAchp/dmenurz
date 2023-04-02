#ifndef _COLOR_HEADERS_
#define _COLOR_HEADERS_

#ifdef COLOR_IMPL

#if THEME == 0
#include "nord.h"
#elif THEME == 1
#include "dracula.h"
#elif THEME == 2
#include "doom-one.h"
#elif THEME == 3
#include "palenight.h"
#elif THEME == 4
#include "monokai-pro.h"
#elif THEME == 5
#include "gruvbox-dark.h"
#elif THEME == 6
#include "oceanic-next.h"
#elif THEME == 7
#include "solarized-dark.h"
#elif THEME == 8
#include "tomorrow-night.h"
#elif THEME == 9
#include "solarized-light.h"
#else
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel] = { "#eeeeee", "#005577" },
	[SchemeSelHighlight] = { "#ffc978", "#005577" },
	[SchemeNormHighlight] = { "#ffc978", "#222222" },
	[SchemeOut] = { "#000000", "#00ffff" },
	[SchemeMid] = { "#eeeeee", "#770000" },
};
#endif

#endif
#endif
