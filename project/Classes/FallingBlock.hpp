//
//  FallingBlock.hpp
//  ColorMatch-desktop
//
//  Created by hoangbui-fe on 6/8/26.
//

#ifndef FallingBlock_hpp
#define FallingBlock_hpp

#include "cocos2d.h"

enum class BlockColor
{
    Blue,
    Red
};

class FallingBlock : public cocos2d::Node
{
public:
    static FallingBlock* create(BlockColor color);

    bool init(BlockColor color);

    BlockColor getBlockColor() const;

    cocos2d::Rect getBounds() const;

    void setBlockColor(BlockColor color);

private:
    FallingBlock();
    virtual ~FallingBlock() override;

private:
    BlockColor _blockColor;
    cocos2d::DrawNode* _drawNode;
};

#endif /* FallingBlock_hpp */
