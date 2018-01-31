#include "DungeonSpace.h"

#include <SDL2/SDL_opengl.h>

#include <limits>
#include <cmath>

Range1D::Range1D()
{
}

Range1D::Range1D(double _min, double _max)
	: min(_min), max(_max), span(max - min)
{
}

Range1D::Range1D(double _min, double _max, double _span)
	: min(_min), max(_max), span(_span)
{
}

Range1D MkRange1D(double _min, double _max)
{
	return Range1D(_min, _max);
}

Range1D MkRange1DFromMin(double _min, double _span)
{
	return Range1D(_min, _min + _span, _span);
}

Range1D MkRange1DFromMax(double _max, double _span)
{
	return Range1D(_max - _span, _max, _span);
}

Range1D MkNoConstraintRange1D()
{
	return Range1D(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
}

Range1D MkMinConstraintRange1D(double _min)
{
	return Range1D(_min, -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
}

Range1D MkMaxConstraintRange1D(double _max)
{
	return Range1D(std::numeric_limits<double>::infinity(), _max, -std::numeric_limits<double>::infinity());
}

Range1D UnionRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range1D((r1.min < r2.min ? r1.min : r2.min), (r1.max > r2.max ? r1.max : r2.max));
}

Range1D IntersectRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range1D((r1.min > r2.min ? r1.min : r2.min), (r1.max < r2.max ? r1.max : r2.max));
}

DrawCheckResult CheckDraw1D(const Range1D& range, const Range1D& screen_range)
{
	if (range.min <= screen_range.min)
	{
		if (range.max <= screen_range.min)
			return DRAW_NONE;
		return DRAW_PART;
	}
	if (range.min < screen_range.max)
	{
		if (range.max < screen_range.max)
			return DRAW_ALL;
		return DRAW_PART;
	}
	return DRAW_NONE;
}


Range2D::Range2D()
{
}

Range2D::Range2D(double _left, double _bottom, double _right, double _top)
	: left(_left), bottom(_bottom), right(_right), top(_top), span_x(right - left), span_y(top - bottom)
{
}

Range2D::Range2D(double _left, double _bottom, double _right, double _top, double _span_x, double _span_y)
	: left(_left), bottom(_bottom), right(_right), top(_top), span_x(_span_x), span_y(_span_y)
{
}

double Range2D::GetMinSpan() const
{
	return (span_x < span_y ? span_x : span_y);
}

double Range2D::GetMaxSpan() const
{
	return (span_x > span_y ? span_x : span_y);
}

Range2D Range2D::GetShiftedRange(double dx, double dy) const
{
	return Range2D(left + dx, bottom + dy, right + dx, top + dy, span_x, span_y);
}

Range1D Range2D::ExtractXRange() const
{
	return Range1D(left, right, span_x);
}

Range1D Range2D::ExtractYRange() const
{
	return Range1D(bottom, top, span_y);
}

void Range2D::DrawRect(float r, float g, float b) const
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2d(left, bottom);
	glVertex2d(right, bottom);
	glVertex2d(right, top);
	glVertex2d(left, top);
	glEnd();
}

Range2D MkRange2D(double _left, double _bottom, double _right, double _top)
{
	return Range2D(_left, _bottom, _right, _top);
}

Range2D MkRange2DFromRange1D(const Range1D& r1, const Range1D& r2)
{
	return Range2D(r1.min, r2.min, r1.max, r2.max);
}

Range2D MkNoConstraintRange2D()
{
	return MkRange2DFromRange1D(MkNoConstraintRange1D(), MkNoConstraintRange1D());
}

Range2D UnionRange2D(const Range2D& r1, const Range2D& r2)
{
	return Range2D(
		(r1.left < r2.left ? r1.left : r2.left),		
		(r1.bottom < r2.bottom ? r1.bottom : r2.bottom),
		(r1.right > r2.right ? r1.right : r2.right),
		(r1.top > r2.top ? r1.top : r2.top));
}

Range2D IntersectRange2D(const Range2D& r1, const Range2D& r2)
{
	return Range2D(
		(r1.left > r2.left ? r1.left : r2.left),		
		(r1.bottom > r2.bottom ? r1.bottom : r2.bottom),
		(r1.right < r2.right ? r1.right : r2.right),
		(r1.top < r2.top ? r1.top : r2.top));
}

Range2D PadRange2D(const Range2D& range, double padding)
{
	return Range2D(range.left - padding, range.bottom - padding, range.right + padding, range.top + padding);
}

DrawCheckResult CheckDraw2D(const Range2D& range, const Range2D& screen_range)
{
	DrawCheckResult check_x = CheckDraw1D(range.ExtractXRange(), screen_range.ExtractXRange());
	DrawCheckResult check_y = CheckDraw1D(range.ExtractYRange(), screen_range.ExtractYRange());

	return (check_x < check_y ? check_x : check_y); // exploit the precedence
}


Room::Room(double _left, double _bottom, double _right, double _top)
	: range(_left, _bottom, _right, _top)
{
}

void Room::Draw(bool is_padded) const
{
	if (is_padded)
	{
		double padding = 5.0; // hard-coded, the wall_min is better set to be no smaller than this
		Range2D modified_range(range.left - padding, range.bottom - padding, range.right + padding, range.top + padding);
		modified_range.DrawRect(0.2, 0.2, 0.2);
	}
	else
	{
		range.DrawRect(0.8, 0.6, 0.4);
	}
}


Corridor::Corridor(double _left, double _bottom, double _right, double _top)
	: range(_left, _bottom, _right, _top)
{
}

void Corridor::Draw(bool is_padded) const
{
	if (is_padded)
	{
		double padding = 5.0; // hard-coded, the wall_min is better set to be no smaller than this
		Range2D modified_range(range.left - padding, range.bottom - padding, range.right + padding, range.top + padding);
		modified_range.DrawRect(0.2, 0.2, 0.2);
	}
	else
	{
		range.DrawRect(0.8, 0.8, 0.0);
	}
}


BossRoom::BossRoom(double _left, double _bottom, double _right, double _top)
	: range(_left, _bottom, _right, _top)
{
}

void BossRoom::Draw(bool is_padded) const
{
	if (is_padded)
	{
		double padding = 5.0; // hard-coded, the wall_min is better set to be no smaller than this
		Range2D modified_range(range.left - padding, range.bottom - padding, range.right + padding, range.top + padding);
		modified_range.DrawRect(0.2, 0.2, 0.2);
	}
	else
	{
		range.DrawRect(0.9, 0.1, 0.1);
	}
}

