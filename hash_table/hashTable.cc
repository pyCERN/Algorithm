#include "hashTable.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int nextPrime(int x) {
  x = (x % 2 == 0) ? x - 1 : x;
  bool isPrime = false;
  while (!isPrime && (x += 2)) {
    isPrime = true;
    for (int i = 3; isPrime && i <= static_cast<int>(std::sqrt(x)); i += 2) {
      isPrime = (x % i != 0);
    }
  }
  return x;
}

void SeparateChainingHashTable::rehash() {
  std::vector<std::vector<int>> oldVec(objVectors.size());

  objVectors.resize(nextPrime(2 * objVectors.size()));
  makeEmpty();

  for (auto& vec : oldVec) {
    for (auto& obj : vec)
      insert(obj);
  }
}

// Separate Chaining Hash Table
int SeparateChainingHashTable::myhash(int x) const {
  static hash hf;
  return hf(x) % objVectors.size();
}

bool SeparateChainingHashTable::contains(int x) const {
  auto& whichVector = objVectors[myhash(x)];
  return std::find(whichVector.begin(), whichVector.end(), x) != whichVector.end();
}

void SeparateChainingHashTable::makeEmpty() {
  currentSize = 0;
  for (auto& objVector : objVectors)
    objVector.clear();
}

bool SeparateChainingHashTable::insert(int x) {
  auto& whichVector = objVectors[myhash(x)];
  if (std::find(whichVector.begin(), whichVector.end(), x) != whichVector.end())
    return false;
  whichVector.push_back(x);
  if (++currentSize > objVectors.size())
    rehash();
  return true;
}

bool SeparateChainingHashTable::remove(int x) {
  auto& whichVector = objVectors[myhash(x)];
  auto it = std::find(whichVector.begin(), whichVector.end(), x);
  if (it == whichVector.end())
    return false;
  whichVector.erase(it);
  currentSize--;
  return true;
}

// Linear Probing Hash Table
int LinearProbingHashTable::myhash(int x) const {
  static hash hf;
  return hf(x) % objVector.size();
}

void LinearProbingHashTable::rehash() {
  std::vector<HashedObjAndStatus> oldVec { objVector };

  objVector.resize(nextPrime(2 * objVector.size()));
  makeEmpty();

  for (auto& hashedObj : oldVec) {
    if (hashedObj.status == OCCUPIED)
      insert(std::move(hashedObj.obj));
  }
}

int LinearProbingHashTable::probe(int x) const {
  int pos = myhash(x), oldPos = pos;
  int i = 0;
  while (objVector[pos].obj != x && objVector[pos].status != EMPTY) {
    pos = (oldPos + collisionResolution(i++)) % objVector.size();
  }
  return pos;
}

bool LinearProbingHashTable::contains(int x) const {
  int pos = probe(x);
  return objVector[pos].obj == x;
}

void LinearProbingHashTable::makeEmpty() {
  currentSize = 0;
  for (size_t i = 0; i < objVector.size(); i++)
    objVector[i].status = EMPTY;
}

bool LinearProbingHashTable::insert(int x) {
  int pos = probe(x);
  bool isInserted = false;

  if (objVector[pos].status != OCCUPIED) {
    objVector[pos].obj = x;
    objVector[pos].status = OCCUPIED;
    isInserted = true;
  }
  
  if (++currentSize > objVector.size() / 2)
    rehash();

  return isInserted;
}

bool LinearProbingHashTable::remove(int x) {
  int pos = probe(x);
  bool isRemoved = false;

  if (objVector[pos].status == OCCUPIED) {
    objVector[pos].status = DELETED;
    isRemoved = true;
  }

  return isRemoved;
}

void LinearProbingHashTable::print() const {
  for (auto& x : objVector) {
    if (x.status == EMPTY) std::cout << "N/A" << "\t" << "EMPTY\n";
    else if (x.status == OCCUPIED) std::cout << x.obj << "\t" << "OCCUPIED\n";
    else std::cout << x.obj << "\t" << "DELETED\n";
  }
}