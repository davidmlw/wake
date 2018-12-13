#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <string>

struct CloneMap;
struct LabelMap;

struct TypeVar {
private:
  mutable TypeVar *parent;

  // before unification, expr children are YOUNGER than their parent
  // before unification, args are YOUNGER than the constructor
  int dob; // date of birth
  int nargs;
  TypeVar *pargs;
  std::string name;

  static void do_clone(TypeVar &out, const TypeVar &x, int dob, CloneMap &clones);
  static void do_format(std::ostream &os, const TypeVar &value, LabelMap &labels, bool parens);

  bool isFree() const { return name.empty(); }

public:
  TypeVar(const TypeVar& other) = delete;
  TypeVar(TypeVar &&other) = delete;
  TypeVar& operator = (const TypeVar &other) = delete;
  TypeVar& operator = (TypeVar &&other) = delete;

  ~TypeVar();
  TypeVar(); // free type-var
  TypeVar(const std::string &name_, int nargs_);

  const TypeVar *find() const;
  TypeVar *find();

  const TypeVar & operator[](int i) const { return find()->pargs[i]; }
  TypeVar & operator[](int i) { return find()->pargs[i]; }
  int getDOB() const { return find()->dob; }

  void setDOB();
  bool unify(TypeVar &other);
  bool unify(TypeVar &&other) { return unify(other); }

  void clone(TypeVar &into, int dob) const;

friend std::ostream & operator << (std::ostream &os, const TypeVar &value);
};

#endif
