#include "CuckooHashTable.h"
#include <math.h>
#include <vector>

CuckooHashTable::CuckooHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  numBucks = numBuckets;
  h1 = family->get();
  h2 = family->get();
  std::vector<int> temp(numBuckets, 0);
  b1 = temp;
  b2 = temp;
  i1 = temp;
  i2 = temp;
  num_elems = 0;
  fam = family;
}

CuckooHashTable::~CuckooHashTable() {
  // TODO: Implement this
}

void CuckooHashTable::rehash(int data){
  std::vector<int> all_elems;
  for(size_t i = 0; i < numBucks; i++) {
    if(i1[i] == 1) {
      all_elems.push_back(b1[i]);
      i1[i] = 0;
    }
    if(i2[i] == 1) {
      all_elems.push_back(b2[i]);
      i2[i] = 0;
    }
  }
  h1 = fam->get();
  h2 = fam->get();
  num_elems = 0;
  for(size_t j = 0; j < all_elems.size(); j++) {
    insert(all_elems[j]);
  }
  insert(data);
}


void CuckooHashTable::insert(int data) {
  // TODO REHASH!!!  
  if(contains(data))
      return;
  double displacements = 0.0;
  num_elems += 1;
  size_t buck = h1(data) % numBucks;
  if(i1[buck] == 0){
    b1[buck] = data;
    i1[buck] = 1;
    return;
  }
  int temp = data;
  size_t counter = 1;
  while(true) {
    displacements += 1;
    if(displacements >= (6*log(num_elems))){
      rehash(data);
      return;
    }
    // First evict
    if(counter % 2 == 0) {
      temp = b2[buck];
      b2[buck] = data;
      data = temp;
      buck = h1(data) % numBucks;
      if(i1[buck] == 0){
        b1[buck] = data;
        i1[buck] = 1;
        break;
      }
    } else {
      temp = b1[buck];
      b1[buck] = data;
      data = temp;
      buck = h2(data) % numBucks;
      if(i2[buck] == 0){
        b2[buck] = data;
        i2[buck] = 1;
        break;
      }
    }

    // Now find next hash
    counter += 1;
  }
}

bool CuckooHashTable::contains(int data) const {
  size_t buck = h1(data) % numBucks;
  size_t buck2 = h2(data) % numBucks;
  if((b1[buck] == data && i1[buck] == 1) || (b2[buck2] == data && i2[buck2] == 1)){
    return true;
  }
  return false;
}

void CuckooHashTable::remove(int data) {
  size_t buck = h1(data) % numBucks;
  if(b1[buck] == data){
    i1[buck] = 0;
    num_elems -= 1;
    return;
  }
  buck = h2(data) % numBucks;
  if(b2[buck] == data){
      num_elems -= 1;
      i2[buck] = 0;
  }
}
