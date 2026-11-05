#pragma once
#include <opxy/effect_page.hpp>

namespace myeffect8 {
// Matches resources.display in definition.json: paths, points, nodes, texts, palette.
using Frame = opxy::draw::Frame<0, 0, 18, 17, 1>;
struct DisplayState { opxy::draw::PageHeader page; };
}
