//
// Created by Pawn on 2020/8/3.
//

#ifndef JEDIS_JSORTEDSET_HH
#define JEDIS_JSORTEDSET_HH


#include "../DataStructure/Skiplist.hh"
#include "../Object/JString.hh"
#include <unordered_map>
#include <sstream>
#include <vector>

class JSortedSet {
public:
  JSortedSet() = default;

  size_t size() const{
    return skiplist.size();
  }
  // 向有序集合添加成员

  void insert(double score, const Jedis::JString& obj)
  {
    ZSkipNode* node =  skiplist.insert(score, obj);
    hashmap[obj] = node;
  }
  // 获取有序集合成员的索引
  size_t get_rank(const Jedis::JString & obj) const
  {
    ZSkipNode *node = hashmap.at(obj);
    return skiplist.get_rank(node->score, obj);
  }
  // 获取有序集合成员的值
  double get_score(const Jedis::JString &obj) const
  {
    return hashmap.at(obj)->score;
  }

  // 获取rank = start-stop成员
  std::vector<Jedis::JString> zrange(long start, long stop, bool is_withscores) const
  {
    std::vector<Jedis::JString>  res;
    int size = skiplist.size();
    start = start >= 0 ? start : size + start;
    stop = stop >= 0 ? stop : size + stop;
    if(start > stop || stop >= size)
      return res;
    int len = stop + 1 - start;

    auto res_vec = skiplist.range(start, stop);
    if(is_withscores)
      res.reserve(len * 2);
    else
      res.reserve(len);

    for(auto x : res_vec)
    {
      res.push_back(x->obj);
      if(is_withscores)
        res.push_back(std::to_string(x->score));
    }
    return res;
  }
private:
  ZSkiplist skiplist;
  std::unordered_map<Jedis::JString, ZSkiplist::SkipNode *> hashmap;
};

#endif // JEDIS_JSORTEDSET_HH
