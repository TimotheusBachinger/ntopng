/*
 *
 * (C) 2013-21 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include "ntop_includes.h"
#include "flow_callbacks_includes.h"

void ExternalAlertCheck::protocolDetected(Flow *f) {
  if (f->hasExternalAlert()) { 
    u_int16_t c_score = 100;
    u_int16_t s_score = 100;
    u_int16_t f_score = 100;

    f->triggerAlert(this, getSeverity(), f_score, c_score, s_score);
    f->triggerAlert(this, f->getExternalSeverity(), f_score, c_score, s_score);
  }
}

/* ***************************************************** */

char* ExternalAlertCheck::getAlertJSONStr(Flow *f) {
  char *json;
 
  json = f->getExternalAlert();

  if (json == NULL)
    return NULL;

  return strdup(json);
}
