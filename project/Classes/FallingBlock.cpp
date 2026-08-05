//
//  FallingBlock.cpp
//  ColorMatch-desktop
//
//  Created by hoangbui-fe on 6/8/26.
//

#include "FallingBlock.hpp"
#include "Constants.h"

USING_NS_CC;

FallingBlock::FallingBlock()
    : _blockColor(BlockColor::Blue)
    , _drawNode(nullptr)
{
}

FallingBlock::~FallingBlock()
{
}

FallingBlock* FallingBlock::create(BlockColor color)
{
    FallingBlock* block = new (std::nothrow) FallingBlock();

    if (block != nullptr &&
        block->init(color))
    {
        block->autorelease();
        return block;
    }

    CC_SAFE_DELETE(block);
    return nullptr;
}

bool FallingBlock::init(BlockColor color)
{
    if (!Node::init())
    {
        return false;
    }

    _drawNode = DrawNode::create();
    addChild(_drawNode);

    setContentSize(
        Size(
            ColorMatch::BLOCK_SIZE,
            ColorMatch::BLOCK_SIZE
        )
    );

    setAnchorPoint(Vec2(0.5f, 0.5f));

    setBlockColor(color);

    return true;
}

BlockColor FallingBlock::getBlockColor() const
{
    return _blockColor;
}

void FallingBlock::setBlockColor(BlockColor color)
{
    _blockColor = color;

    _drawNode->clear();

    const float halfSize =
        ColorMatch::BLOCK_SIZE * 0.5f;

    const Vec2 vertices[4] =
    {
        Vec2(-halfSize, -halfSize),
        Vec2( halfSize, -halfSize),
        Vec2( halfSize,  halfSize),
        Vec2(-halfSize,  halfSize)
    };

    Color4F fillColor;

    if (_blockColor == BlockColor::Blue)
    {
        fillColor = Color4F(0.2f, 0.4f, 1.0f, 1.0f);
    }
    else
    {
        fillColor = Color4F(1.0f, 0.2f, 0.2f, 1.0f);
    }

    _drawNode->drawSolidPoly(
        vertices,
        4,
        fillColor
    );
}

Rect FallingBlock::getBounds() const
{
    const float halfSize =
        ColorMatch::BLOCK_SIZE * 0.5f;

    return Rect(
        getPositionX() - halfSize,
        getPositionY() - halfSize,
        ColorMatch::BLOCK_SIZE,
        ColorMatch::BLOCK_SIZE
    );
}
