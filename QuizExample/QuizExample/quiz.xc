giglstart;

gigltype MathQuiz:
< disable auto_prob_noneg, auto_prob_norm >
{
wrapper:
	generator { root = generate Expr(0); }
	string Translate() { return root->Translate(0); }

node:
	string Translate(int preced);
	int Evaluate();

nonterminal:
	Expr(int depth);

rule:
	Expr :=
	| mulexpr: Expr* lexpr, Expr* rexpr
		{
			generator { lexpr = generate Expr(depth + 1);
				rexpr = generate Expr(depth + 1); }
			Translate = lexpr->Translate(1) + " * " + rexpr->Translate(1);
			Evaluate = lexpr->Evaluate() * rexpr->Evaluate();
		}
	| addexpr: Expr* lexpr, Expr* rexpr
		{
			generator { lexpr = generate Expr(depth + 1);
				rexpr = generate Expr(depth + 1); }
			Translate = ( preced > 0 ?
				"( " + lexpr->Translate(0) + " + " + rexpr->Translate(0) + " )" :
				lexpr->Translate(0) + " + " + rexpr->Translate(0) );
			Evaluate = lexpr->Evaluate() + rexpr->Evaluate();
		}
	| intexpr{int min_int, int max_int}: int val
		{
			generator { val = GetRandInt(min_int, max_int); }
			Translate = IntToStr(val);
			Evaluate = val;
		}
};

void GenerateQuizListIncDiffic(MathQuiz** list)
{
	int diffic = 0;
	giglconfig quiz_config = <* MathQuiz:
		Expr :=
		| mulexpr @ {(depth < diffic ? 0.3 : 0.0)}
		| addexpr @ {(depth < diffic ? 0.7 : 0.0)}
		| intexpr{diffic * 5, diffic * 10 + 10} @ {depth >= diffic} *>;
	for (; diffic < 5; diffic++)
		list[diffic] = generate MathQuiz with quiz_config;
}
