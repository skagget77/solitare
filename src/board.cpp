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

#include <ostream>

#include "board.h"

using namespace solitare;

void solitare::start(std::vector<board_t>& boards) {
  board_t board = 0x001C3E7F7F7F3E1CULL;
  board_t frame = 0xFFE3C1808080C1E3ULL;
  board_t mask0 = 0x0010000000000000ULL;

  while (mask0 > 0x0000000000000002ULL) {
    if ((mask0 & frame) == 0 && (mask0 & board) != 0) {
      boards.push_back(board ^ mask0);
    }

    mask0 >>= 1;
  }
}

std::size_t solitare::generate(board_t board, std::vector<board_t>& boards) {
  std::size_t size = boards.size();
  
  board_t frame = 0xFFE3C1808080C1E3ULL;

  // Horizontal moves.
  board_t mask0 = 0x001C000000000000ULL;
  board_t mask1 = 0x0018000000000000ULL;
  board_t mask2 = 0x000C000000000000ULL;
  
  while (mask0 > 0x000000000000000EULL) {
    if ((mask0 & frame) == 0) {
      if ((board & mask0) == mask1 || (board & mask0) == mask2) {
	boards.push_back(board ^ mask0);
      }
    }

    mask0 >>= 1;
    mask1 >>= 1;
    mask2 >>= 1;
  }

  // Vertical moves.
  mask0 = 0x0010101000000000ULL;
  mask1 = 0x0010100000000000ULL;
  mask2 = 0x0000101000000000ULL;
  
  while (mask0 > 0x0000000000020202ULL) {
    if ((mask0 & frame) == 0) {
      if ((board & mask0) == mask1 || (board & mask0) == mask2) {
	boards.push_back(board ^ mask0);
      }
    }

    mask0 >>= 1;
    mask1 >>= 1;
    mask2 >>= 1;
  }
  
  return boards.size() - size;
}

void Board::write(std::ostream& out) const
{
  uint64_t mask = 0x40000000000000ULL;

  while(mask != 0) {
    out << (m_board & mask ? 'O' : '-');

    // Break line at end of each byte.
    if(mask & 0x01010101010101ULL) {
      out << std::endl;
      mask >>= 1;
    }

    mask >>= 1;
  }  
}
