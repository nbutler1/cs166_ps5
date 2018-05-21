#ifndef LinearProbingHashTable_Included
#define LinearProbingHashTable_Included

#include "Hashes.h"

class LinearProbingHashTable {
public:
  /**
   * Constructs a new linear probing table with the specified number of buckets,
   * using hash functions drawn from the indicated family of hash functions.
   * Because our testing harness attempts to exercise a number of different
   * load factors, you should not change the number of buckets once the hash
   * table has initially be created.
   *
   * You can choose a hash function out of the family of hash functions by
   * declaring a variable of type HashFunction and assigning it the value
   * family->get(). For example:
   *
   *    HashFunction h;
   *    h = family->get();
   */
  LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family);
  
  /**
   * Cleans up all memory allocated by this hash table.
   */
  ~LinearProbingHashTable();
  
  /**
   * Inserts the specified element into this hash table. If the element already
   * exists, this operation is a no-op.
   */
  void insert(int key);
  
  /**
   * Returns whether the specified key is contained in this hash tasble.
   */
  bool contains(int key) const;
  
  /**
   * Removes the specified element from this hash table. If the element is not
   * present in the hash table, this operation is a no-op.
   *
   * You should implement this operation using tombstone deletion - replace the
   * key to remove with a special "tombstone" value indicating that something
   * that was stored here has since been removed.
   */
  void remove(int key);
  
private:
  /* TODO: Add any data members or private helper functions that you'll need,
   * then delete this comment.
   */
  
  
  /* Fun with C++: these next two lines disable implicitly-generated copy
   * functions that would otherwise cause weird errors if you tried to
   * implicitly copy an object of this type. You don't need to touch these
   * lines.
   */
  // Array of buckets containing data
  int* buckets;

  // Array of indicators for each spot.
  // These values will be as follows:
  //    -1 is tombstone inidcating a removed element
  //    0 is empty
  //    1 is currently filled
  int* indicators;
  size_t numBucks;
  HashingFunction TableHash;
  LinearProbingHashTable(LinearProbingHashTable const &) = delete;
  void operator=(LinearProbingHashTable const &) = delete;
  size_t increment(size_t bucket);
};

#endif
