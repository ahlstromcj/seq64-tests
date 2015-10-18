/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          gui_assistant_dummy.cpp
 *
 *  This module declares/defines the base class for handling many facets
 *  of using a GUI, without being tied to it.
 *
 * \library       sequencer64 application
 * \author        Chris Ahlstrom
 * \date          2015-10-18
 * \updates       2015-10-18
 * \license       GNU GPLv2 or above
 *
 */

#include "gui_assistant_dummy.hpp"      // seq64::gui_assistant_dummy

/**
 *  Provides a pre-made keys_perform object.  This object is set into
 *  the reference provided in the gui_assistant base class.
 */

seq64::keys_perform gui_assistant_dummy::sm_internal_keys;

/**
 *  Principal constructor.
 */

gui_assistant_dummy::gui_assistant_dummy ()
 :
    seq64::gui_assistant    (sm_internal_keys)
{
    // Empty body
}

/*
 * gui_assistant_dummy.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

