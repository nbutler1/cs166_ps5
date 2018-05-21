#include "SecondChoiceHashTable.h"

SecondChoiceHashTable::SecondChoiceHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family) {
  for(size_t i = 0; i < numBuckets; i++){
    b1.push_back({});
    b2.push_back({});
  }
  numBucks = numBuckets;
  h1 = family->get();
  h2 = family->get();
}

SecondChoiceHashTable::~SecondChoiceHashTable() {
  // TODO: Implement this
}


void SecondChoiceHashTable::insert(int data) {
  if(contains(data))
    return;
  size_t buck1 = h1(data) % numBucks;
  size_t buck2 = h2(data) % numBucks;
  if(b1[buck1].size() < b2[buck2].size()){
      b1[buck1].push_back(data);
  }else{
      b2[buck2].push_back(data);
  }
}

bool SecondChoiceHashTable::contains(int data) const {
  size_t buck1 = h1(data) % numBucks;
  size_t buck2 = h2(data) % numBucks;
  for(size_t i = 0; i < b1[buck1].size(); i++){
    if(b1.at(buck1).at(i) == data)
        return true;
  } 
  for(size_t i = 0; i < b2[buck2].size(); i++){
    if(b2.at(buck2).at(i) == data)
        return true;
  } 
  return false;
}

void SecondChoiceHashTable::remove(int data) {
  // TODO: Implement this
  size_t buck1 = h1(data) % numBucks;
  size_t buck2 = h2(data) % numBucks;
  for(size_t i = 0; i < b1[buck1].size(); i++){
    if(b1.at(buck1).at(i) == data){
        b1.at(buck1).erase(b1.at(buck1).begin() + i);
        return;
    }
  } 
  for(size_t i = 0; i < b2[buck2].size(); i++){
    if(b2.at(buck2).at(i) == data){
        b2.at(buck2).erase(b2.at(buck2).begin() + i);
        return;
    }
  } 
}
