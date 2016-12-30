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

#pragma once

#include <cstdint>
#include <ctime>
#include <iosfwd>

namespace solitare {
/**
 * Progress class, outputs progress information roughly every 5 seconds.
 *
 */
class Progress
{
public:
  /**
   * Constructor.
   *
   * @param out Output stream where the progress information is written.
   */
  Progress(std::ostream& out);

  // Prevent copying.
  Progress(const Progress&) = delete;
  Progress& operator=(const Progress&) = delete;

  /**
   * Tick progress forward one step.
   */
  void tick();
  
private:
  std::ostream& m_out;
  std::clock_t m_clock;
  std::uint64_t m_ticks;
  std::uint64_t m_ticks_bucket;
};
}
