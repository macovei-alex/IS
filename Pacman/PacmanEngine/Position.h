#pragma once

#include "Dimensions.h"
#include <limits> 

namespace pac
{
    struct Position
    {
        decltype(Dimensions::rows) row = 0;
        decltype(Dimensions::cols) col = 0;

        static Position GetInvalid()
        {
            return {
                std::numeric_limits<decltype(row)>::max(),
                std::numeric_limits<decltype(col)>::max()
            };
        }

        bool IsValid() const
        {
            return row != std::numeric_limits<decltype(row)>::max() &&
                col != std::numeric_limits<decltype(col)>::max();
        }

        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }

        bool operator!=(const Position& other) const {
            return !(*this == other); 
        }

        // Less-than operator for use in sorted containers like std::map and std::set
        bool operator<(const Position& other) const {
            if (row < other.row) return true;
            if (row > other.row) return false;
            return col < other.col;
        }
    };
}
