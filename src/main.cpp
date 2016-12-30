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

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "board.h"
#include "progress.h"

// Select the best pop-count available.
#if defined(__GNUC__)
#if defined(__x86_64__)
#include "nmmintrin.h"
#define popcnt _mm_popcnt_u64
#else
#define popcnt __builtin_popcountll
#endif
#else
#define popcnt basic_popcount
#endif

using namespace solitare;

namespace {
  // Basic pop-count implementation used as fallback.
  __attribute__((unused))
  std::size_t basic_popcount(std::uint64_t word) {
    std::size_t count = 0;

    for (int i = 0; i < 64; i++) {
      if ((word & (1ULL << i)) != 0) {
	count++;
      }
    }

    return count;
  }
}

/**
 * Searches board collection for a solution. Any solution found will be returned
 * in reverse order.
 *
 * @param progress Progress information.
 * @param boards Boards.
 * @param solution Solution found, empty if no solution was found.
 * @param pruned Pruned boards, i.e. boards not leading to a solution.
 * @return True if a solution was found, false otherwise.
 */
bool search(Progress& progress,
	    std::vector<board_t>& boards,
	    std::vector<board_t>& solution,
	    std::unordered_set<board_t>& pruned) {
  progress.tick();

  // Pick newest board.
  board_t board = boards.back();

  // Single marble remaining equals solution.
  if (popcnt(board) == 1) {
    solution.push_back(board);
    return true;
  }

  if (pruned.count(board) == 0) {
    // Append all possible new boards to the boards collection.
    std::size_t count = generate(board, boards);

    // Evaluate all new boards.
    for (std::size_t i = 0; i < count; i++) {
      if (search(progress, boards, solution, pruned)) {
	solution.push_back(board);
	return true;
      }

      // Remove new boards not leading to a solution.
      boards.pop_back();
    }

    pruned.emplace(board);
  }

  return false;
}

/**
 * Main application entry-point.
 */
int main() {
  Progress progress(std::cout);

  std::vector<board_t> boards;
  boards.reserve(35 * 35);

  std::vector<board_t> solution;
  solution.reserve(36);

  // Boards already seen not leading to a solution.
  std::unordered_set<board_t> pruned;

  start(boards);

  if (search(progress, boards, solution, pruned)) {
    std::cout << "Solution:" << std::endl << std::endl;

    // Output solution in reverse order.
    for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
      std::cout << Board(*it) << std::endl;
    }
  }
  else {
    std::cout << "No solution found!" << std::endl << std::endl;
  }
}
