#include "GiglDefaultInclude.h"

#include "TreeSegment.h"

class LTree_Node;
class TreePart;
class MbBranch;

class LTree_Node
{
public:
	virtual ~LTree_Node() {}
	Vector2D start_pos;
	Vector2D end_pos;
	Range2D bound_box;
	virtual void Draw()
	{
		switch (CheckDraw2D(bound_box, window_range))
		{
		case DRAW_NONE: break;
		case DRAW_PART: DrawPart(); break;
		case DRAW_ALL: DrawAll(); break;
		}
	}
	virtual void DrawPart() = 0;
	virtual void DrawAll() = 0;
};

class TreePart : public LTree_Node
{
public:
	virtual ~TreePart() {}
};

class MbBranch : public LTree_Node
{
public:
	virtual ~MbBranch() {}
};

class ntTree : public TreePart
{
public:
	ntTree(TreePart* _bottom, MbBranch* _right, MbBranch* _left, TreePart* _top)
		: bottom(_bottom), right(_right), left(_left), top(_top)
	{
		start_pos = bottom->start_pos;
		end_pos = top->end_pos;
		bound_box = UnionRange2D(right->bound_box, UnionRange2D(left->bound_box, UnionRange2D(bottom->bound_box, top->bound_box)));
	}
	virtual ~ntTree()
	{
		delete bottom;
		delete right;
		delete left;
		delete top;
	}
	TreePart* bottom;
	MbBranch* right;
	MbBranch* left;
	TreePart* top;
	void DrawPart()
	{
		bottom->Draw();
		top->Draw();
		right->Draw();
		left->Draw();
	}
	void DrawAll()
	{
		bottom->DrawAll();
		top->DrawAll();
		right->DrawAll();
		left->DrawAll();
	}
};

class termTree : public TreePart
{
public:
	termTree(TreeSegment* _seg) : seg(_seg)
	{
		start_pos = seg->start;
		end_pos = seg->end;
		bound_box = seg->range;
	}
	virtual ~termTree() { delete seg; }
	TreeSegment* seg;
	void DrawPart() { seg->Draw(); }
	void DrawAll() { seg->Draw(); }
};

class justBranch : public MbBranch
{
public:
	justBranch(TreePart* _treepart) : treepart(_treepart)
	{
		bound_box = treepart->bound_box;
	}
	virtual ~justBranch() { delete treepart; }
	TreePart* treepart;
	void DrawPart() { treepart->Draw(); }
	void DrawAll() { treepart->DrawAll(); }
};

class noBranch : public MbBranch
{
public:
	noBranch()
	{
		bound_box = MkNoConstraintRange2D();
	}
	virtual ~noBranch() {}
	void DrawPart() {}
	void DrawAll() {}
};

enum ConfigInstance { DETERM_TREE, ND_TREE, ADV_ND_TREE };

double ntFac(int d, int n, double w, double max_w)
{
	return d < n ? 0.5 + w/max_w : 0.0;
}

double brchFac(double w, double max_w)
{
	return  2.5 - 3*w/max_w;
}

double getBranchDeg(ConfigInstance instance)
{
	switch (instance)
	{
	case DETERM_TREE:
		return 45.0;
	case ND_TREE:
		return GetRandFloat(30.0, 60.0);
	case ADV_ND_TREE:
		return GetRandFloat(30.0, 60.0);
	}
}

TreePart* Generate_TreePart(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w, int n, double unit_len, double max_wid, ConfigInstance instance);
MbBranch* Generate_MbBranch(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, int n, double unit_len, double max_wid, ConfigInstance instance);

TreePart* Generate_TreePart(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, double top_w, int n, double unit_len, double max_wid, ConfigInstance instance)
{
	double probs[2];
	switch (instance)
	{
	case DETERM_TREE:
		probs[0] = depth < n;
		probs[1] = 1.0 - probs[0];
		break;
	case ND_TREE:
		probs[0] = depth < n ? 0.8 : 0.0;
		probs[1] = 1.0 - probs[0];
		break;
	case ADV_ND_TREE:
		probs[0] = ntFac(depth, n, bottom_w, max_wid);
		probs[1] = 1.0 - probs[0];
		break;
	}
	NonegativeProbs(probs, 2);
	NormalizeProbs(probs, 2);
	int choice = GetRandChoiceFromProbs(probs, 2);

	switch (choice)
	{
	case 0:
	{
		double mid_w = 0.5 * (bottom_w + top_w);
		TreePart* bottom = Generate_TreePart(depth + 1, start, dir, bottom_w, mid_w, n, unit_len, max_wid, instance);
		MbBranch* right = Generate_MbBranch(depth + 1, bottom->end_pos, RotateDegrees(dir, -getBranchDeg(instance)), mid_w, n, unit_len, max_wid, instance);
		MbBranch* left = Generate_MbBranch(depth + 1, bottom->end_pos, RotateDegrees(dir, getBranchDeg(instance)), mid_w, n, unit_len, max_wid, instance);
		TreePart* top = Generate_TreePart(depth + 1, bottom->end_pos, dir, mid_w, top_w, n, unit_len, max_wid, instance);
		
		return new ntTree(bottom, right, left, top);
	}
	case 1:
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
		TreeSegment* seg = new TreeSegment(start, start + unit_len * dir, dir, unit_len, seg_w);

		return new termTree(seg);
	}
	}

	return nullptr;
}

MbBranch* Generate_MbBranch(int depth, const Vector2D& start, const Vector2D& dir, double bottom_w, int n, double unit_len, double max_wid, ConfigInstance instance)
{
	double probs[2];
	switch (instance)
	{
	case DETERM_TREE:
		probs[0] = 1.0;
		probs[1] = 0.0;
		break;
	case ND_TREE:
		probs[0] = 0.7;
		probs[1] = 0.3;
		break;
	case ADV_ND_TREE:
		probs[0] = brchFac(bottom_w, max_wid);
		probs[1] = 1.0 - probs[0];
		break;
	}
	NonegativeProbs(probs, 2);
	NormalizeProbs(probs, 2);
	int choice = GetRandChoiceFromProbs(probs, 2);	

	switch (choice)
	{
	case 0:
	{
		TreePart* treepart = Generate_TreePart(depth, start, dir, bottom_w, 0.0, n, unit_len, max_wid, instance);

		return new justBranch(treepart);
	}
	case 1:
	{
		return new noBranch();
	}
	}

	return nullptr;
}

class LTree
{
public:
	LTree(int _n, double _unit_len, double _max_wid, ConfigInstance _instance)
		: root(Generate_TreePart(0, MkVector2D(0.0, 0.0), MkVector2D(0.0, 1.0), _max_wid, 0.0, _n, _unit_len, _max_wid, _instance)),
		bound_box(root->bound_box) {}
	~LTree() { delete root; }
	LTree_Node* root;
	Range2D bound_box;
	void Draw() { root->Draw(); }
};

LTree* GenerateDetermLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return new LTree(n, unit_len, max_wid, DETERM_TREE);
}

LTree* GenerateNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return new LTree(n, unit_len, max_wid, ND_TREE);
}

LTree* GenerateAdvNDLTree(int n, double unit_len)
{
	double max_wid = (double)(1 << n);
	return new LTree(n, unit_len, max_wid, ADV_ND_TREE);
}
