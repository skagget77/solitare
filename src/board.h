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
#include <iosfwd>
#include <vector>

namespace solitare {
/**
 * Bit-board, a 1 represents a marble and a 0 empty space. 37 of the 64
 * available bits are used for the game board.
 */
typedef std::uint64_t board_t;

/**
 * Generate all 37 possible start positions. The start positions are all
 * appended to the boards collection.
 *
 * @param boards Collection of boards to evaluate during solution search.
 */
void start(std::vector<board_t>& boards);

/**
 * Generate all possible new positions using the specified board as start
 * position. The new positions are all appended to the boards collection.
 *
 * @param board Start position.
 * @param boards Collection of boards to evaluate during solution search.
 *
 * @return Number of new boards generated. 0 implies that we have reached a
 *     leaf-node in the game tree. Note that a leaf-node does not imply that
 *     there is a single marble left.
 */
std::size_t generate(board_t board, std::vector<board_t>& boards);

/**
 * Board class, tags bit-boards as boards when writing them to a stream. Avoids
 * mixing up regular 64-bit unsigned integers and bit-boards.
 *
 */
class Board {
public:
  /**
   * Constructor.
   *
   * @param board Bit-board.
   */
  Board(board_t board)
    : m_board(board) {
  }

  /**
   * Writes this board to the specified output stream.
   *
   * @param out Output stream.
   */
  void write(std::ostream& out) const;

private:
  board_t m_board;
};

/**
 * Writes the specified board to the output stream.
 *
 * @param out Output stream.
 * @param board Board.
 * @return Output stream.
 */
inline std::ostream& operator<<(std::ostream& out, const Board& board) {
  board.write(out);
  return out;
}
}
