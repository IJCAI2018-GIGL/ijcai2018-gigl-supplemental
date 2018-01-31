
#include "GiglDefaultInclude.h"


#include "TreeSegment.h"


class Range2D;

class Vector2D;

class TreeSegment;


class LTree;

class LTree__Node;

class LTree__TreePart;

class LTree__MbBranch;

class LTree__ntTree;

class LTree__termTree;

class LTree__justBranch;

class LTree__noBranch;

class LTree {
public:
  LTree(const GiglConfig  & input__config);
  LTree(GiglConfig  && input__config);
  LTree(LTree__Node  * input__root);
  LTree(const GiglConfig  & input__config, LTree__Node  * input__root);
  LTree(GiglConfig  && input__config, LTree__Node  * input__root);
  ~LTree();
  GiglConfig config;
  signed int n;
  double unit_len;
  double max_wid;
  LTree__Node  *root;
  Vector2D start_pos;
  Vector2D end_pos;
  Range2D bound_box;
  void Draw();
  void DrawPart();
  void DrawAll();
  LTree__TreePart  *Generate__TreePart(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__ntTree  *Generate__ntTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__termTree  *Generate__termTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__MbBranch  *Generate__MbBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
  LTree__justBranch  *Generate__justBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
  LTree__noBranch  *Generate__noBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
  

};
class LTree__Node {
public:
  LTree__Node(LTree  * input__item);
  LTree__Node();
  virtual ~LTree__Node();
  LTree  *item;
  Vector2D start_pos;
  Vector2D end_pos;
  Range2D bound_box;
  void virtual Draw();
  void virtual DrawPart() = 0;
  void virtual DrawAll() = 0;
  

};
class LTree__TreePart : public LTree__Node {
public:
  LTree__TreePart(LTree  * input__item);
  LTree__TreePart();
  

};
class LTree__MbBranch : public LTree__Node {
public:
  LTree__MbBranch(LTree  * input__item);
  LTree__MbBranch();
  

};
class LTree__ntTree : public LTree__TreePart {
public:
  LTree__ntTree(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__ntTree(LTree__TreePart  * input__bottom, LTree__MbBranch  * input__right, LTree__MbBranch  * input__left, LTree__TreePart  * input__top);
  ~LTree__ntTree();
  LTree__TreePart  *bottom;
  LTree__MbBranch  *right;
  LTree__MbBranch  *left;
  LTree__TreePart  *top;
  void DrawPart();
  void DrawAll();
  

};
class LTree__termTree : public LTree__TreePart {
public:
  LTree__termTree(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
  LTree__termTree(TreeSegment  * input__seg);
  ~LTree__termTree();
  TreeSegment  *seg;
  void DrawPart();
  void DrawAll();
  

};
class LTree__justBranch : public LTree__MbBranch {
public:
  LTree__justBranch(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
  LTree__justBranch(LTree__TreePart  * input__treepart);
  ~LTree__justBranch();
  LTree__TreePart  *treepart;
  void DrawPart();
  void DrawAll();
  

};
class LTree__noBranch : public LTree__MbBranch {
public:
  LTree__noBranch(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
  LTree__noBranch(void);
  ~LTree__noBranch();
  void DrawPart();
  void DrawAll();
  

};
LTree::LTree(const GiglConfig  & input__config) : config((input__config)), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config))))
{

  {
    ((root) = ((Generate__TreePart)(0, ((MkVector2D)(0.0, 0.0)), ((MkVector2D)(0.0, 1.0)), (max_wid), 0.0)));
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
  ((bound_box) = ((root)->bound_box));
}

LTree::LTree(GiglConfig  && input__config) : config(((move)((input__config)))), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config))))
{

  {
    ((root) = ((Generate__TreePart)(0, ((MkVector2D)(0.0, 0.0)), ((MkVector2D)(0.0, 1.0)), (max_wid), 0.0)));
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
  ((bound_box) = ((root)->bound_box));
}

LTree::LTree(LTree__Node  * input__root) : config(), n(), unit_len(), max_wid(), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
  ((bound_box) = ((root)->bound_box));
}

LTree::LTree(const GiglConfig  & input__config, LTree__Node  * input__root) : config((input__config)), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
  ((bound_box) = ((root)->bound_box));
}

LTree::LTree(GiglConfig  && input__config, LTree__Node  * input__root) : config(((move)((input__config)))), n((((signed int (*)(const GiglConfig  & ))(((config).funcs)[0]))((config)))), unit_len((((double (*)(const GiglConfig  & ))(((config).funcs)[1]))((config)))), max_wid((((double (*)(const GiglConfig  & ))(((config).funcs)[2]))((config)))), root((input__root))
{

  if ((root))
  {
    (((root)->item) = (this));
  } else {
    
  }
  ((start_pos) = ((root)->start_pos));
  ((end_pos) = ((root)->end_pos));
  ((bound_box) = ((root)->bound_box));
}

LTree::~LTree()
{

  if ((root))
  {
    delete (root);
  } else {
    
  }
}









void LTree::Draw()
{

  return (((root)->Draw)());
}

void LTree::DrawPart()
{

  return (((root)->DrawPart)());
}

void LTree::DrawAll()
{

  return (((root)->DrawAll)());
}

LTree__TreePart  *LTree::Generate__TreePart(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  double probs[2] = {(((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[3]))((config), (depth), (start), (dir), (bottom_w), (top_w))), (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[4]))((config), (depth), (start), (dir), (bottom_w), (top_w)))};;
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));;
  switch ((choice))
  {
    case 0:
      return ((Generate__ntTree)((depth), (start), (dir), (bottom_w), (top_w)));
    
    case 1:
      return ((Generate__termTree)((depth), (start), (dir), (bottom_w), (top_w)));
    
  }
  return 0;
}

LTree__ntTree  *LTree::Generate__ntTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  LTree__ntTree  *node = (new LTree__ntTree((this), (depth), (start), (dir), (bottom_w), (top_w)));;
  
  
  
  
  {
    double mid_w = (0.5 * (((bottom_w) + (top_w))));;
    (((node)->bottom) = ((Generate__TreePart)(((depth) + 1), (start), (dir), (bottom_w), (mid_w))));
    (((node)->right) = ((Generate__MbBranch)(((depth) + 1), (((node)->bottom)->end_pos), ((RotateDegrees)((dir), (-(((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[5]))((config), (depth), (start), (dir), (bottom_w), (top_w)))))), (mid_w))));
    (((node)->left) = ((Generate__MbBranch)(((depth) + 1), (((node)->bottom)->end_pos), ((RotateDegrees)((dir), (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  , double  ))(((config).funcs)[5]))((config), (depth), (start), (dir), (bottom_w), (top_w))))), (mid_w))));
    (((node)->top) = ((Generate__TreePart)(((depth) + 1), (((node)->bottom)->end_pos), (dir), (mid_w), (top_w))));
    (((node)->start_pos) = (start));
    (((node)->end_pos) = (((node)->top)->end_pos));
    (((node)->bound_box) = ((UnionRange2D)((((node)->right)->bound_box), ((UnionRange2D)((((node)->left)->bound_box), ((UnionRange2D)((((node)->bottom)->bound_box), (((node)->top)->bound_box))))))));
  }
  return (node);
}

LTree__termTree  *LTree::Generate__termTree(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  LTree__termTree  *node = (new LTree__termTree((this), (depth), (start), (dir), (bottom_w), (top_w)));;
  
  {
    double seg_w;;
    if (((depth) >= (n)))
    {
      {
        ((seg_w) = ((((top_w) < 1e-7) ? (-1.0) : (0.5 * (((bottom_w) + (top_w)))))));
      }
    } else {
      {
        double factor = (1.0 / ((double)((1 << ((((n) - (depth)) + 1))))));;
        ((seg_w) = ((((1.0 - (factor))) * (bottom_w)) + ((factor) * (top_w))));
      }
    }
    (((node)->start_pos) = (start));
    (((node)->end_pos) = ((start) + ((unit_len) * (dir))));
    (((node)->seg) = (new TreeSegment((start), ((node)->end_pos), (dir), (unit_len), (seg_w))));
    (((node)->bound_box) = (((node)->seg)->range));
  }
  return (node);
}

LTree__MbBranch  *LTree::Generate__MbBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  double probs[2] = {(((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  ))(((config).funcs)[6]))((config), (depth), (start), (dir), (bottom_w))), (((double (*)(const GiglConfig  & , signed int  , const Vector2D  & , const Vector2D  & , double  ))(((config).funcs)[7]))((config), (depth), (start), (dir), (bottom_w)))};;
  ((NonegativeProbs)((probs), 2));
  
  ((NormalizeProbs)((probs), 2));
  signed int choice = ((GetRandChoiceFromProbs)((probs), 2));;
  switch ((choice))
  {
    case 0:
      return ((Generate__justBranch)((depth), (start), (dir), (bottom_w)));
    
    case 1:
      return ((Generate__noBranch)((depth), (start), (dir), (bottom_w)));
    
  }
  return 0;
}

LTree__justBranch  *LTree::Generate__justBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  LTree__justBranch  *node = (new LTree__justBranch((this), (depth), (start), (dir), (bottom_w)));;
  
  {
    (((node)->treepart) = ((Generate__TreePart)((depth), (start), (dir), (bottom_w), 0.0)));
    (((node)->bound_box) = (((node)->treepart)->bound_box));
  }
  return (node);
}

LTree__noBranch  *LTree::Generate__noBranch(signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  LTree__noBranch  *node = (new LTree__noBranch((this), (depth), (start), (dir), (bottom_w)));;
  (((node)->bound_box) = ((MkNoConstraintRange2D)()));
  return (node);
}



LTree__Node::LTree__Node(LTree  * input__item) : item((input__item))
{

  
}

LTree__Node::LTree__Node()
{

  
}

LTree__Node::~LTree__Node()
{

  
}





void LTree__Node::Draw()
{

  {
    switch (((CheckDraw2D)((bound_box), (window_range))))
    {
      {
        case (DRAW_NONE):
          break;
        
        case (DRAW_PART):
          ((DrawPart)());
        
        break;
        case (DRAW_ALL):
          ((DrawAll)());
        
        break;
      }
    }
  }
}





LTree__TreePart::LTree__TreePart(LTree  * input__item) : LTree__Node((input__item))
{

  
}

LTree__TreePart::LTree__TreePart()
{

  
}



LTree__MbBranch::LTree__MbBranch(LTree  * input__item) : LTree__Node((input__item))
{

  
}

LTree__MbBranch::LTree__MbBranch()
{

  
}



LTree__ntTree::LTree__ntTree(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w) : LTree__TreePart((input__item))
{

  
}

LTree__ntTree::LTree__ntTree(LTree__TreePart  * input__bottom, LTree__MbBranch  * input__right, LTree__MbBranch  * input__left, LTree__TreePart  * input__top) : bottom((input__bottom)), right((input__right)), left((input__left)), top((input__top))
{

  if ((bottom))
  {
    (((bottom)->item) = (item));
  } else {
    
  }
  if ((left))
  {
    (((left)->item) = (item));
  } else {
    
  }
  if ((right))
  {
    (((right)->item) = (item));
  } else {
    
  }
  if ((top))
  {
    (((top)->item) = (item));
  } else {
    
  }
  
}

LTree__ntTree::~LTree__ntTree()
{

  
  {
    if ((bottom))
    {
      delete (bottom);
    } else {
      
    }
  }
  {
    if ((left))
    {
      delete (left);
    } else {
      
    }
  }
  {
    if ((right))
    {
      delete (right);
    } else {
      
    }
  }
  {
    if ((top))
    {
      delete (top);
    } else {
      
    }
  }
}





void LTree__ntTree::DrawPart()
{

  {
    (((bottom)->Draw)());
    (((top)->Draw)());
    (((right)->Draw)());
    (((left)->Draw)());
  }
}

void LTree__ntTree::DrawAll()
{

  {
    (((bottom)->DrawAll)());
    (((top)->DrawAll)());
    (((right)->DrawAll)());
    (((left)->DrawAll)());
  }
}



LTree__termTree::LTree__termTree(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w) : LTree__TreePart((input__item))
{

  
}

LTree__termTree::LTree__termTree(TreeSegment  * input__seg) : seg((input__seg))
{

  
  
}

LTree__termTree::~LTree__termTree()
{

  
  {
    if ((seg))
    {
      delete (seg);
    } else {
      
    }
  }
}


void LTree__termTree::DrawPart()
{

  return (((seg)->Draw)());
}

void LTree__termTree::DrawAll()
{

  return (((seg)->Draw)());
}



LTree__justBranch::LTree__justBranch(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w) : LTree__MbBranch((input__item))
{

  
}

LTree__justBranch::LTree__justBranch(LTree__TreePart  * input__treepart) : treepart((input__treepart))
{

  if ((treepart))
  {
    (((treepart)->item) = (item));
  } else {
    
  }
  
}

LTree__justBranch::~LTree__justBranch()
{

  
  {
    if ((treepart))
    {
      delete (treepart);
    } else {
      
    }
  }
}


void LTree__justBranch::DrawPart()
{

  return (((treepart)->Draw)());
}

void LTree__justBranch::DrawAll()
{

  return (((treepart)->DrawAll)());
}



LTree__noBranch::LTree__noBranch(LTree  * input__item, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w) : LTree__MbBranch((input__item))
{

  
}

LTree__noBranch::LTree__noBranch(void)
{

  ((bound_box) = ((MkNoConstraintRange2D)()));
}

LTree__noBranch::~LTree__noBranch()
{

  
}

void LTree__noBranch::DrawPart()
{

  
}

void LTree__noBranch::DrawAll()
{

  
}




signed int LTree__ConfigLambda__112__37(const GiglConfig  & config);
double LTree__ConfigLambda__112__40(const GiglConfig  & config);
double LTree__ConfigLambda__112__50(const GiglConfig  & config);
double LTree__ConfigLambda__113__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__113__30(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__113__51(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__114__24(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
double LTree__1__ConfigLambda__114__2(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
signed int LTree__ConfigLambda__112__37(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__112__40(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__112__50(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__113__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return 45.0;
}
double LTree__ConfigLambda__113__30(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((depth) < (*(*((signed int * *)(((config).vars)[3])))));
}
double LTree__ConfigLambda__113__51(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - ((depth) < (*(*((signed int * *)(((config).vars)[3]))))));
}
double LTree__ConfigLambda__114__24(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return (1.0 - 0.0);
}
double LTree__1__ConfigLambda__114__2(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return 0.0;
}

LTree  *GenerateDetermLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));;
    return (new LTree((GiglConfig(4, 8, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + (sizeof(signed int *))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n)))))}), (IndexVec{0, 1, 2, 5, 3, 4, 6, 7}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__112__37))), ((FuncPtr)(&(LTree__ConfigLambda__112__40))), ((FuncPtr)(&(LTree__ConfigLambda__112__50))), ((FuncPtr)(&(LTree__ConfigLambda__113__21))), ((FuncPtr)(&(LTree__ConfigLambda__113__30))), ((FuncPtr)(&(LTree__ConfigLambda__113__51))), ((FuncPtr)(&(LTree__ConfigLambda__114__24))), ((FuncPtr)(&(LTree__1__ConfigLambda__114__2)))})))));
  }
}
signed int LTree__ConfigLambda__120__37(const GiglConfig  & config);
double LTree__ConfigLambda__120__40(const GiglConfig  & config);
double LTree__ConfigLambda__120__50(const GiglConfig  & config);
double LTree__ConfigLambda__121__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__121__50(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__121__83(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__122__28(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
double LTree__ConfigLambda__122__43(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
signed int LTree__ConfigLambda__120__37(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__120__40(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__120__50(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__121__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((GetRandFloat)(30.0, 60.0));
}
double LTree__ConfigLambda__121__50(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (((depth) < (*(*((signed int * *)(((config).vars)[3]))))) ? 0.8 : 0.0);
}
double LTree__ConfigLambda__121__83(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - (((depth) < (*(*((signed int * *)(((config).vars)[3]))))) ? 0.8 : 0.0));
}
double LTree__ConfigLambda__122__28(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return 0.7;
}
double LTree__ConfigLambda__122__43(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return (1.0 - 0.7);
}

LTree  *GenerateNDLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));;
    return (new LTree((GiglConfig(4, 8, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + (sizeof(signed int *))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n)))))}), (IndexVec{0, 1, 2, 5, 3, 4, 6, 7}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__120__37))), ((FuncPtr)(&(LTree__ConfigLambda__120__40))), ((FuncPtr)(&(LTree__ConfigLambda__120__50))), ((FuncPtr)(&(LTree__ConfigLambda__121__21))), ((FuncPtr)(&(LTree__ConfigLambda__121__50))), ((FuncPtr)(&(LTree__ConfigLambda__121__83))), ((FuncPtr)(&(LTree__ConfigLambda__122__28))), ((FuncPtr)(&(LTree__ConfigLambda__122__43)))})))));
  }
}

double ntFac(signed int  d, signed int  n, double  w, double  max_w)
{

  {
    return (((d) < (n)) ? (0.5 + ((w) / (max_w))) : 0.0);
  }
}

double brchFac(double  w, double  max_w)
{

  {
    return (2.5 - ((3 * (w)) / (max_w)));
  }
}
signed int LTree__ConfigLambda__138__37(const GiglConfig  & config);
double LTree__ConfigLambda__138__40(const GiglConfig  & config);
double LTree__ConfigLambda__138__50(const GiglConfig  & config);
double LTree__ConfigLambda__139__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__139__50(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__139__96(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w);
double LTree__ConfigLambda__140__28(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
double LTree__ConfigLambda__140__66(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w);
signed int LTree__ConfigLambda__138__37(const GiglConfig  & config)
{

  return (*(*((signed int * *)(((config).vars)[0]))));
}
double LTree__ConfigLambda__138__40(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[1]))));
}
double LTree__ConfigLambda__138__50(const GiglConfig  & config)
{

  return (*(*((double * *)(((config).vars)[2]))));
}
double LTree__ConfigLambda__139__21(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((GetRandFloat)(30.0, 60.0));
}
double LTree__ConfigLambda__139__50(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return ((ntFac)((depth), (*(*((signed int * *)(((config).vars)[3])))), (bottom_w), (*(*((double * *)(((config).vars)[4]))))));
}
double LTree__ConfigLambda__139__96(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w, double  top_w)
{

  return (1.0 - ((ntFac)((depth), (*(*((signed int * *)(((config).vars)[3])))), (bottom_w), (*(*((double * *)(((config).vars)[4])))))));
}
double LTree__ConfigLambda__140__28(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return ((brchFac)((bottom_w), (*(*((double * *)(((config).vars)[5]))))));
}
double LTree__ConfigLambda__140__66(const GiglConfig  & config, signed int  depth, const Vector2D  & start, const Vector2D  & dir, double  bottom_w)
{

  return (1.0 - ((brchFac)((bottom_w), (*(*((double * *)(((config).vars)[5])))))));
}

LTree  *GenerateAdvNDLTree(signed int  n, double  unit_len)
{

  {
    double max_wid = ((double)((1 << (n))));;
    return (new LTree((GiglConfig(6, 8, ((sizeof(signed int *)) + ((sizeof(double *)) + ((sizeof(double *)) + ((sizeof(signed int *)) + ((sizeof(double *)) + (sizeof(double *))))))), (SizeVec{(sizeof(signed int *)), (sizeof(double *)), (sizeof(double *)), (sizeof(signed int *)), (sizeof(double *)), (sizeof(double *))}), (VarPtrVec{((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(unit_len))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((signed int * *)((malloc)((sizeof(signed int *)))))) = (&(n))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid))))), ((VarPtr)(&((*((double * *)((malloc)((sizeof(double *)))))) = (&(max_wid)))))}), (IndexVec{0, 1, 2, 5, 3, 4, 6, 7}), (FuncPtrVec{((FuncPtr)(&(LTree__ConfigLambda__138__37))), ((FuncPtr)(&(LTree__ConfigLambda__138__40))), ((FuncPtr)(&(LTree__ConfigLambda__138__50))), ((FuncPtr)(&(LTree__ConfigLambda__139__21))), ((FuncPtr)(&(LTree__ConfigLambda__139__50))), ((FuncPtr)(&(LTree__ConfigLambda__139__96))), ((FuncPtr)(&(LTree__ConfigLambda__140__28))), ((FuncPtr)(&(LTree__ConfigLambda__140__66)))})))));
  }
}

