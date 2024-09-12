#ifndef __HASHTABLE__
#define __HASHTABLE__
#include <vector>

struct hash {
  int operator()(int key) const { return key; }
};

// Interface
class HashTable {
public:
  virtual bool contains(int x) const = 0;

  virtual void makeEmpty()   = 0;
  virtual bool insert(int x) = 0;
  virtual bool remove(int x) = 0;

  virtual ~HashTable() = default;

private:
  virtual void rehash() = 0;

  virtual int  myhash(int x) const = 0;
};

class SeparateChainingHashTable : public HashTable {
public:
  SeparateChainingHashTable(int tableSize = 101) {
    objVectors.reserve(tableSize);
  }

  bool contains(int x) const override;

  void makeEmpty()   override;
  bool insert(int x) override;
  bool remove(int x) override;

private:
  std::vector<std::vector<int>> objVectors;
  int currentSize { 0 };

  void rehash() override;

  int  myhash(int x) const override;
};

class LinearProbingHashTable : public HashTable {
public:
  LinearProbingHashTable(int tableSize = 101) {
    objVector = std::vector<HashedObjAndStatus>(tableSize);
    makeEmpty();
  }

  bool contains(int x) const override;

  void makeEmpty()   override;
  bool insert(int x) override;
  bool remove(int x) override;

  void print() const;

  enum CellStatus { EMPTY, OCCUPIED, DELETED }; // DELETED is for lazy deletion for successful probe operaiton after remove.

private:
  struct HashedObjAndStatus {
    int obj;
    CellStatus status;

    HashedObjAndStatus(int _obj = 0, CellStatus _status = EMPTY)
      : obj { _obj }, status { _status }
    {}
  };

  std::vector<HashedObjAndStatus> objVector;
  int currentSize { 0 };

  void rehash() override;

  int myhash(int x) const override;
  int collisionResolution(int i) const { return i; }
  int probe(int x) const;
};

#endif