#include <game_objects.hpp>

#include <array>

GameBoard::GameBoard(){}
GameBoard::GameBoard(size_t x, size_t y) : grid(x,y){}

void GameBoard::CalculateNumbers(){

    std::array<std::pair<int, int>, 8> directions = {{
        {-1,-1}, {0,-1}, {1,-1}, // TopRow
        {-1,0}, {1,0}, // MiddleRow
        {-1,1}, {0,1}, {1,1}}}; // BottomRow
    for(size_t x=0; x< grid.getX(); x++){
        for(size_t y=0; y< grid.getY(); y++){

            // Reset count of tile;
            grid(x,y).count = 0;

            for(auto& direction : directions){

                // Skip if tile is outofbound
                int neighborX = x + direction.first, neighborY = y + direction.second;
                if(grid.isOutOfBound(neighborX, neighborY)){
                    continue;
                }

                // Calculate count
                if(grid(neighborX, neighborY).mBomb){
                    grid(x,y).count ++;
                }
            }
        }
    }
}