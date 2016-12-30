/*
 * Solitare, a brute-force solution to the Marble Solitare game.
 * Copyright (C) 2017  Johan Andersson
 *
 * This file is part of Solitare.
 *
 * Solitare is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solitare is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Solitare.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iomanip>
#include <iostream>

#include "progress.h"

using namespace solitare;

Progress::Progress(std::ostream& out)
  : m_out(out)
  , m_clock(std::clock() / CLOCKS_PER_SEC)
  , m_ticks(0)
  , m_ticks_bucket(0) {
}

void Progress::tick() {
  m_ticks_bucket++;

  // Bucket ticks to avoid running time calculation for every tick.
  if (m_ticks_bucket > 10000) {
    m_ticks += m_ticks_bucket;

    // Calculate time elapsed since last stream output. Output at most once
    // every 1 second.
    std::clock_t diff = std::clock() / CLOCKS_PER_SEC - m_clock;

    if(diff > 1) {
      m_clock += diff;

      double tps = double(m_ticks) / m_clock;

      m_out << "Searching tree, " << std::setw(15) << m_ticks << " ticks @ "
	    << tps << " ticks/second." << std::endl;
    }

    m_ticks_bucket = 0;
  }
}
