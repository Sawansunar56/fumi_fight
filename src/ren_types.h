#pragma once
#include "my_maths.h"

// Colors specified here
constexpr v4 CLR_WHITE        = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr v4 CLR_RED          = {1.0f, 0.0f, 0.0f, 1.0f};
constexpr v4 CLR_BLUE         = {0.0f, 0.0f, 1.0f, 1.0f};
constexpr v4 CLR_GREEN        = {0.0f, 1.0f, 0.0f, 1.0f};
constexpr v4 CLR_BLACK        = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr v4 CLR_CYAN         = {0.0f, 1.0f, 1.0f, 1.0f};
constexpr v4 CLR_YELLOW       = {1.0f, 1.0f, 0.0f, 1.0f};
constexpr v4 CLR_PURPLE       = {1.0f, 0.0f, 1.0f, 1.0f};
constexpr v4 CLR_TEAL         = {0.0f, 0.502f, 0.502f, 1.0f};
constexpr v4 CLR_VIOLET       = {0.561f, 0.0f, 1.0f, 1.0f};
constexpr v4 CLR_CRIMSON      = {0.863f, 0.078f, 0.235f, 1.0f};
constexpr v4 CLR_ROYAL_BLUE   = {0.255f, 0.412f, 0.882f, 1.0f};
constexpr v4 CLR_CHARCOAL     = {0.212f, 0.271f, 0.31f, 1.0f};
constexpr v4 CLR_CHOCOLATE    = {0.482f, 0.247f, 0.0f, 1.0f};
constexpr v4 CLR_TEAL_GREEN   = {0.0f, 0.427f, 0.357f, 1.0f};
constexpr v4 CLR_BLUE_GROTTO  = {0.016f, 0.463f, 0.816f, 1.0f};
constexpr v4 CLR_BLUE_GREEN   = {0.051f, 0.596f, 0.729f, 1.0f};
constexpr v4 CLR_BLUE_IRIS    = {0.353f, 0.31f, 0.812f, 1.0f};
constexpr v4 CLR_CHILLI_PAPER = {0.89f, 0.133f, 0.153f, 1.0f};

struct Vertex
{
    v3 position;
    v4 color;
    v2 uv0;
    f32 texture_index;
};
