giglstart;

import "TreeSegment.h";

class Range2D;
class Vector2D;
class TreeSegment;

gigltype LTree{int n, double unit_len, double max_wid}:
{
wrapper:
	generator
	{
		root = generate TreePart(0, MkVector2D(0.0, 0.0), MkVector2D(0.0, 1.0), max_wid, 0.0);
	}

node:
	Vector2D start_pos;
	Vector2D end_pos;
	Range2D bound_box;
	void Draw()
	{
		switch (CheckDraw2D(bound_box, window_range))
		{
			case DRAW_NONE: break;
			case DRAW_PART: DrawPart(); break;
			case DRAW_ALL: DrawAll(); break;
		}
	}
	void DrawPart();
	void DrawAll();

nonterminal:
	TreePart(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w);
	MbBranch(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w);

rule:
	TreePart :=
	| ntTree{dynamic double branch_deg}: TreePart* bottom, MbBranch* right, MbBranch* left, TreePart* top
		{
			generator
			{
				double mid_w = 0.5 * (bottom_w + top_w);
				bottom = generate TreePart(depth + 1, start, dir, bottom_w, mid_w);
				right = generate MbBranch(depth + 1, bottom->end_pos, RotateDegrees(dir, -branch_deg), mid_w);
				left = generate MbBranch(depth + 1, bottom->end_pos, RotateDegrees(dir, branch_deg), mid_w);
				top = generate TreePart(depth + 1, bottom->end_pos, dir, mid_w, top_w);
				start_pos = start;
				end_pos = top->end_pos;
				bound_box = UnionRange2D(right->bound_box, UnionRange2D(left->bound_box, UnionRange2D(bottom->bound_box, top->bound_box)));
			}
			DrawPart
			{
				bottom->Draw();
				top->Draw();
				right->Draw();
				left->Draw();
			}
			DrawAll
			{
				bottom->DrawAll();
				top->DrawAll();
				right->DrawAll();
				left->DrawAll();
			}
		}
	| termTree: TreeSegment* seg
		{
			generator
			{
				double seg_w;
				if (depth >= n)
				{
					seg_w = (top_w < 1e-7 ? -1.0 : 0.5 * (bottom_w + top_w)); // negative means draw as a leaf
				}
				else
				{
					double factor = 1.0 / (double)(1 << (n - depth + 1));
					seg_w = (1.0 - factor) * bottom_w + factor * top_w; // linear interpolation
				}
				start_pos = start;
				end_pos = start + unit_len * dir;
				seg = new TreeSegment(start, end_pos, dir, unit_len, seg_w);
				bound_box = seg->range;
			}
			DrawPart = seg->Draw();
			DrawAll = seg->Draw();
		}

	MbBranch :=
	| justBranch: TreePart* treepart
		{
			generator
			{
				treepart = generate TreePart(depth, start, dir, bottom_w, 0.0);
				bound_box = treepart->bound_box;
			}
			DrawPart = treepart->Draw();
			DrawAll = treepart->DrawAll();
		}
	| noBranch:
		{
			bound_box = MkNoConstraintRange2D();
			DrawPart {}
			DrawAll {}
		}
};

LTree* GenerateDetermLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{45.0} @ {depth < n} | termTree,
		MbBranch := justBranch *>;
}

LTree* GenerateNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{GetRandFloat(30.0, 60.0)} @ {depth < n ? 0.8 : 0.0} | termTree,
		MbBranch := justBranch @ {0.7} | noBranch *>;
}

double ntFac(int d, int n, double w, double max_w)
{
	return d < n ? 0.5 + w/max_w : 0.0;
}

double brchFac(double w, double max_w)
{
	return  2.5 - 3*w/max_w;
}

LTree* GenerateAdvNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return generate LTree with <* LTree{n, unit_len, max_wid}:
		TreePart := ntTree{GetRandFloat(30.0, 60.0)} @ {ntFac(depth, n, bottom_w, max_wid)} | termTree,
		MbBranch := justBranch @ {brchFac(bottom_w, max_wid)} | noBranch *>;
}
