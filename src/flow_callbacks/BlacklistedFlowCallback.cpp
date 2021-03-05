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

void BlacklistedFlowCallback::protocolDetected(Flow *f) {
  ntop->getTrace()->traceEvent(TRACE_NORMAL, "%s()", __FUNCTION__);
  
  if(f->isBlacklistedFlow()) {
    u_int16_t c_score, s_score, f_score = 100;
    
    if(f->isBlacklistedServer())
      c_score = SCORE_MAX_SCRIPT_VALUE, s_score = 5;
    else
      c_score = 5, s_score = 10;

    f->setStatus(status_blacklisted, f_score, c_score, s_score, "" /* ?? */, script_category_security);

    /* Call this only ONE time after all the flow callbacks have been executed, only on the PREDOMINANT status */
    triggerAlert(f,
		 status_blacklisted, /* The status set. Make this a BlacklistedFlowCallback class member? */
		 alert_flow_blacklisted, /* Alert ids are != from status ids. Merge them (e.g., first 128 alert ids == flow statuses)? */
		 alert_level_error, /* Severity, TODO: read it from the alert configuration */
		 f_score, /* The score used to setStatus() */
		 NULL /* A possible JSON specific to this alert, e.g,. getJSONAlert(f) */);
  }

  /* TODO emit flow alert */
}
