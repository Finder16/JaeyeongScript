#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

Preferences* _new_preferences(void) {
  Preferences* preferences = (Preferences*)jcalloc(sizeof(Preferences));
  preferences->os = PREF_OS_AUTO;
  preferences->backend = PREF_BACKEND_AUTO;
  preferences->output_mode = PREF_OUTPUTMODE_STDOUT;
  return preferences;
}