#include "GiglDefaultInclude.h"

class Expr
{
public:
	virtual ~Expr() {}
	virtual string Translate(int preced) = 0;
	virtual int Evaluate() = 0;
};

class mulexpr : public Expr
{
public:
	mulexpr(Expr* _lexpr, Expr* _rexpr) : lexpr(_lexpr), rexpr(_rexpr) {}
	~mulexpr() { delete lexpr; delete rexpr; }
	Expr* lexpr;
	Expr* rexpr;

	string Translate(int preced)
	{ 
		return lexpr->Translate(1) + " * " + rexpr->Translate(1);
	}

	int Evaluate()
	{
		return lexpr->Evaluate() * rexpr->Evaluate();
	}
	
};

class addexpr : public Expr
{
public:
	addexpr(Expr* _lexpr, Expr* _rexpr) : lexpr(_lexpr), rexpr(_rexpr) {}
	~addexpr() { delete lexpr; delete rexpr; }
	Expr* lexpr;
	Expr* rexpr;

	string Translate(int preced)
	{
		return preced > 0 ?
			"( " + lexpr->Translate(0) + " + " + rexpr->Translate(0) + " )" :
			lexpr->Translate(0) + " + " + rexpr->Translate(0);
	}

	int Evaluate()
	{
		return lexpr->Evaluate() + rexpr->Evaluate();
	}
};

class intexpr : public Expr
{
public:
	intexpr(int _val) : val(_val) {}
	int val;

	string Translate(int preced)
	{
		return IntToStr(val);
	}

	int Evaluate()
	{
		return val;
	}
};

Expr* Generate_Expr(int diffic, int depth)
{
	double probs[3] = { (depth < diffic ? 0.3 : 0.0), (depth < diffic ? 0.7 : 0.0), (depth >= diffic) };
	int choice = GetRandChoiceFromProbs(probs, 3);

	switch (choice)
	{
	case 0:
		return new mulexpr(Generate_Expr(diffic, depth + 1), Generate_Expr(diffic, depth + 1));
	case 1:
		return new addexpr(Generate_Expr(diffic, depth + 1), Generate_Expr(diffic, depth + 1));
	case 2:
		return new intexpr(GetRandInt(diffic * 5, diffic * 10 + 10));
	}

	return nullptr;
}

class MathQuiz
{
public:
	MathQuiz(int diffic) : root(Generate_Expr(diffic, 0)) {}
	~MathQuiz() { delete root; }
	Expr* root;

	string Translate()
	{
		return root->Translate(0);
	}

	int Evaluate()
	{
		return root->Evaluate();
	}
};

void GenerateQuizListIncDiffic(MathQuiz** list)
{
	int diffic = 0;
	for (; diffic < 5; diffic++)
		list[diffic] = new MathQuiz(diffic);
}
