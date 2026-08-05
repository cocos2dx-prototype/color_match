//
//  Constants.h
//  ColorMatch-desktop
//
//  Created by hoangbui-fe on 6/8/26.
//

#ifndef Constants_h
#define Constants_h

namespace ColorMatch
{
    // -------------------------------------------------------------------------
    // Window / Resolution
    // -------------------------------------------------------------------------
    constexpr float DESIGN_WIDTH  = 1280.0f;
    constexpr float DESIGN_HEIGHT = 720.0f;

    // -------------------------------------------------------------------------
    // Player
    // -------------------------------------------------------------------------
    constexpr float PLAYER_SIZE  = 40.0f;
    constexpr float PLAYER_SPEED = 320.0f;

    constexpr float PLAYER_START_X = DESIGN_WIDTH * 0.5f;
    constexpr float PLAYER_START_Y = 80.0f;

    // -------------------------------------------------------------------------
    // Falling Blocks
    // -------------------------------------------------------------------------
    constexpr float BLOCK_SIZE  = 40.0f;
    constexpr float BLOCK_SPEED = 180.0f;

    constexpr float BLOCK_START_X = DESIGN_WIDTH * 0.5f;
    constexpr float BLOCK_START_Y =
        DESIGN_HEIGHT + (BLOCK_SIZE * 0.5f);

    // -------------------------------------------------------------------------
    // Gameplay
    // -------------------------------------------------------------------------
    constexpr int TOTAL_BLOCKS     = 6;
    constexpr int SCORE_PER_MATCH  = 10;

    // -------------------------------------------------------------------------
    // HUD
    // -------------------------------------------------------------------------
    constexpr float SCORE_LABEL_X = 20.0f;
    constexpr float SCORE_LABEL_Y = DESIGN_HEIGHT - 20.0f;

    constexpr float BLOCKS_LABEL_X = DESIGN_WIDTH * 0.5f;
    constexpr float BLOCKS_LABEL_Y = DESIGN_HEIGHT - 20.0f;

    // -------------------------------------------------------------------------
    // Result Message
    // -------------------------------------------------------------------------
    constexpr float RESULT_LABEL_X = DESIGN_WIDTH * 0.5f;
    constexpr float RESULT_LABEL_Y = DESIGN_HEIGHT * 0.5f;
}

#endif /* Constants_h */
