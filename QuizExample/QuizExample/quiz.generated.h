
#include "GiglDefaultInclude.h"



class MathQuiz;

class MathQuiz__Node;

class MathQuiz__Expr;

class MathQuiz__mulexpr;

class MathQuiz__addexpr;

class MathQuiz__intexpr;

class MathQuiz {
public:
  MathQuiz(const GiglConfig  & input__config);
  MathQuiz(GiglConfig  && input__config);
  MathQuiz(MathQuiz__Node  * input__root);
  MathQuiz(const GiglConfig  & input__config, MathQuiz__Node  * input__root);
  MathQuiz(GiglConfig  && input__config, MathQuiz__Node  * input__root);
  ~MathQuiz();
  GiglConfig config;
  MathQuiz__Node  *root;
  string Translate();
  string Translate(signed int  preced);
  signed int Evaluate();
  MathQuiz__Expr  *Generate__Expr(signed int  depth);
  MathQuiz__mulexpr  *Generate__mulexpr(signed int  depth);
  MathQuiz__addexpr  *Generate__addexpr(signed int  depth);
  MathQuiz__intexpr  *Generate__intexpr(signed int  depth);
  

};
class MathQuiz__Node {
public:
  MathQuiz__Node(MathQuiz  * input__item);
  MathQuiz__Node();
  virtual ~MathQuiz__Node();
  MathQuiz  *item;
  string virtual Translate(signed int  preced) = 0;
  signed int virtual Evaluate() = 0;
  

};
class MathQuiz__Expr : public MathQuiz__Node {
public:
  MathQuiz__Expr(MathQuiz  * input__item);
  MathQuiz__Expr();
  

};
class MathQuiz__mulexpr : public MathQuiz__Expr {
public:
  MathQuiz__mulexpr(MathQuiz  * input__item, signed int  depth);
  MathQuiz__mulexpr(MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr);
  ~MathQuiz__mulexpr();
  MathQuiz__Expr  *lexpr;
  MathQuiz__Expr  *rexpr;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
class MathQuiz__addexpr : public MathQuiz__Expr {
public:
  MathQuiz__addexpr(MathQuiz  * input__item, signed int  depth);
  MathQuiz__addexpr(MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr);
  ~MathQuiz__addexpr();
  MathQuiz__Expr  *lexpr;
  MathQuiz__Expr  *rexpr;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
class MathQuiz__intexpr : public MathQuiz__Expr {
public:
  MathQuiz__intexpr(MathQuiz  * input__item, signed int  depth);
  MathQuiz__intexpr(signed int  input__val);
  ~MathQuiz__intexpr();
  signed int min_int;
  signed int max_int;
  signed int val;
  string Translate(signed int  preced);
  signed int Evaluate();
  

};
MathQuiz::MathQuiz(const GiglConfig  & input__config) : config((input__config))
{

  {
    ((root) = ((Generate__Expr)(0)));
  }
}

MathQuiz::MathQuiz(GiglConfig  && input__config) : config(((move)((input__config))))
{

  {
    ((root) = ((Generate__Expr)(0)));
  }
}

MathQuiz::MathQuiz(MathQuiz__Node  * input__root) : config(), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
}

MathQuiz::MathQuiz(const GiglConfig  & input__config, MathQuiz__Node  * input__root) : config((input__config)), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
}

MathQuiz::MathQuiz(GiglConfig  && input__config, MathQuiz__Node  * input__root) : config(((move)((input__config)))), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
}

MathQuiz::~MathQuiz()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}



string MathQuiz::Translate()
{

  {
    return (((root)->Translate)(0));
  }
}

string MathQuiz::Translate(signed int  preced)
{

  return (((root)->Translate)((preced)));
}

signed int MathQuiz::Evaluate()
{

  return (((root)->Evaluate)());
}

MathQuiz__Expr  *MathQuiz::Generate__Expr(signed int  depth)
{

  double probs[3] = {(((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[0]))((config), (depth))), (((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[1]))((config), (depth))), (((double (*)(const GiglConfig  & , signed int  ))(((config).funcs)[2]))((config), (depth)))};;
  
  
  
  signed int choice = ((GetRandChoiceFromProbs)((probs), 3));;
  switch ((choice))
  {
    case 0:
      return ((Generate__mulexpr)((depth)));
    
    case 1:
      return ((Generate__addexpr)((depth)));
    
    case 2:
      return ((Generate__intexpr)((depth)));
    
  }
  return 0;
}

MathQuiz__mulexpr  *MathQuiz::Generate__mulexpr(signed int  depth)
{

  MathQuiz__mulexpr  *node = (new MathQuiz__mulexpr((this), (depth)));;
  
  
  {
    (((node)->lexpr) = ((Generate__Expr)(((depth) + 1))));
    (((node)->rexpr) = ((Generate__Expr)(((depth) + 1))));
  }
  return (node);
}

MathQuiz__addexpr  *MathQuiz::Generate__addexpr(signed int  depth)
{

  MathQuiz__addexpr  *node = (new MathQuiz__addexpr((this), (depth)));;
  
  
  {
    (((node)->lexpr) = ((Generate__Expr)(((depth) + 1))));
    (((node)->rexpr) = ((Generate__Expr)(((depth) + 1))));
  }
  return (node);
}

MathQuiz__intexpr  *MathQuiz::Generate__intexpr(signed int  depth)
{

  MathQuiz__intexpr  *node = (new MathQuiz__intexpr((this), (depth)));;
  
  {
    (((node)->val) = ((GetRandInt)(((node)->min_int), ((node)->max_int))));
  }
  return (node);
}



MathQuiz__Node::MathQuiz__Node(MathQuiz  * input__item) : item((input__item))
{

  
}

MathQuiz__Node::MathQuiz__Node()
{

  
}

MathQuiz__Node::~MathQuiz__Node()
{

  
}






MathQuiz__Expr::MathQuiz__Expr(MathQuiz  * input__item) : MathQuiz__Node((input__item))
{

  
}

MathQuiz__Expr::MathQuiz__Expr()
{

  
}



MathQuiz__mulexpr::MathQuiz__mulexpr(MathQuiz  * input__item, signed int  depth) : MathQuiz__Expr((input__item))
{

  
}

MathQuiz__mulexpr::MathQuiz__mulexpr(MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr) : lexpr((input__lexpr)), rexpr((input__rexpr))
{

  if ((lexpr))
  {
    (((lexpr)->item) = (item));
  } else {
    
  }
  if ((rexpr))
  {
    (((rexpr)->item) = (item));
  } else {
    
  }
  
}

MathQuiz__mulexpr::~MathQuiz__mulexpr()
{

  
  {
    if ((lexpr))
    {
      delete (lexpr);
    } else {
      
    }
  }
  {
    if ((rexpr))
    {
      delete (rexpr);
    } else {
      
    }
  }
}



string MathQuiz__mulexpr::Translate(signed int  preced)
{

  return (((((lexpr)->Translate)(1)) + " * ") + (((rexpr)->Translate)(1)));
}

signed int MathQuiz__mulexpr::Evaluate()
{

  return ((((lexpr)->Evaluate)()) * (((rexpr)->Evaluate)()));
}



MathQuiz__addexpr::MathQuiz__addexpr(MathQuiz  * input__item, signed int  depth) : MathQuiz__Expr((input__item))
{

  
}

MathQuiz__addexpr::MathQuiz__addexpr(MathQuiz__Expr  * input__lexpr, MathQuiz__Expr  * input__rexpr) : lexpr((input__lexpr)), rexpr((input__rexpr))
{

  if ((lexpr))
  {
    (((lexpr)->item) = (item));
  } else {
    
  }
  if ((rexpr))
  {
    (((rexpr)->item) = (item));
  } else {
    
  }
  
}

MathQuiz__addexpr::~MathQuiz__addexpr()
{

  
  {
    if ((lexpr))
    {
      delete (lexpr);
    } else {
      
    }
  }
  {
    if ((rexpr))
    {
      delete (rexpr);
    } else {
      
    }
  }
}



string MathQuiz__addexpr::Translate(signed int  preced)
{

  return ((((preced) > 0) ? (((("( " + (((lexpr)->Translate)(0))) + " + ") + (((rexpr)->Translate)(0))) + " )") : (((((lexpr)->Translate)(0)) + " + ") + (((rexpr)->Translate)(0)))));
}

signed int MathQuiz__addexpr::Evaluate()
{

  return ((((lexpr)->Evaluate)()) + (((rexpr)->Evaluate)()));
}



MathQuiz__intexpr::MathQuiz__intexpr(MathQuiz  * input__item, signed int  depth) : MathQuiz__Expr((input__item)), min_int((((signed int (*)(const GiglConfig  & , signed int  ))((((item)->config).funcs)[3]))(((item)->config), (depth)))), max_int((((signed int (*)(const GiglConfig  & , signed int  ))((((item)->config).funcs)[4]))(((item)->config), (depth))))
{

  
}

MathQuiz__intexpr::MathQuiz__intexpr(signed int  input__val) : min_int(), max_int(), val((input__val))
{

  
  
}

MathQuiz__intexpr::~MathQuiz__intexpr()
{

  
  {
    
  }
}




string MathQuiz__intexpr::Translate(signed int  preced)
{

  return ((IntToStr)((val)));
}

signed int MathQuiz__intexpr::Evaluate()
{

  return (val);
}




double MathQuiz__ConfigLambda__48__15(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__49__15(const GiglConfig  & config, signed int  depth);
signed int MathQuiz__ConfigLambda__50__12(const GiglConfig  & config, signed int  depth);
signed int MathQuiz__ConfigLambda__50__24(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__50__45(const GiglConfig  & config, signed int  depth);
double MathQuiz__ConfigLambda__48__15(const GiglConfig  & config, signed int  depth)
{

  return ((((depth) < (*(*((signed int * *)(((config).vars)[0]))))) ? 0.3 : 0.0));
}
double MathQuiz__ConfigLambda__49__15(const GiglConfig  & config, signed int  depth)
{

  return ((((depth) < (*(*((signed int * *)(((config).vars)[1]))))) ? 0.7 : 0.0));
}
signed int MathQuiz__ConfigLambda__50__12(const GiglConfig  & config, signed int  depth)
{

  return ((*(*((signed int * *)(((config).vars)[2])))) * 5);
}
signed int MathQuiz__ConfigLambda__50__24(const GiglConfig  & config, signed int  depth)
{

  return (((*(*((signed int * *)(((config).vars)[3])))) * 10) + 10);
}
double MathQuiz__ConfigLambda__50__45(const GiglConfig  & config, signed int  depth)
{

  return ((depth) >= (*(*((signed int * *)(((config).vars)[4])))));
}

void GenerateQuizListIncDiffic(MathQuiz  * * list)
{

  {
    signed int diffic = 0;;
    GiglConfig quiz_config = (GiglConfig(5, 5, ((sizeof(signed int *)) + ((sizeof(signed int *)) + ((sizeof(signed int *)) + ((sizeof(signed int *)) + (sizeof(signed int *)))))), (SizeVec{(sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(diffic)))))}), (IndexVec{0, 1, 3, 4, 2}), (FuncPtrVec{((FuncPtr)(&(MathQuiz__ConfigLambda__48__15))), ((FuncPtr)(&(MathQuiz__ConfigLambda__49__15))), ((FuncPtr)(&(MathQuiz__ConfigLambda__50__12))), ((FuncPtr)(&(MathQuiz__ConfigLambda__50__24))), ((FuncPtr)(&(MathQuiz__ConfigLambda__50__45)))})));;
    for(; ((diffic) < 5); ((diffic)++))
    {
      (((list)[(diffic)]) = (new MathQuiz((quiz_config))));
    }
  }
}

