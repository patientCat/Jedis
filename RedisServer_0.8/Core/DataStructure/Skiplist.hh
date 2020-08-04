#pragma once
#include <string>

#include <vector>
// 模仿Redis中的跳表学习
// 1. val 节点值
template <size_t SkiplistMaxLevel>
class Skiplist {
  constexpr static const double SkipListP = 0.5;
public:

  struct SkipNode{
    SkipNode(double a_score, const std::string &a_obj, int a_max_level = SkiplistMaxLevel)
        : score(a_score)
        , obj(a_obj)
    {

    }

    std::string obj;
    double score;
    SkipNode *backward;
    struct SkipNodeLevel{
      SkipNode *forward{nullptr};
      unsigned int span{0};
    }level_node[SkiplistMaxLevel];
  };

  Skiplist()
  {
    max_level_ = 1;
    length_ = 0;
    header_ = new SkipNode(0, "");
    header_->backward = nullptr;
    tail_ = nullptr;
  }


  // 插入一个新节点
  SkipNode * insert(double score, const std::string&  obj)
  {
    SkipNode *update[SkiplistMaxLevel], *x;
    // rank 是用来帮助计算后序的span值用的
    unsigned int rank[SkiplistMaxLevel];
    int i, level;

    // assert score != NAN

    // 在各个层查找节点的插入位置
    // T_wrost = O(N^2), T_avg = O(N log N)
    x = header_;
    for (i = max_level_ -1; i >= 0; i--) {

      /* store rank that is crossed to reach the insert position */
      // 如果 i 不是 max_level_-1 层
      // 那么 i 层的起始 rank 值为 i+1 层的 rank 值
      // 各个层的 rank 值一层层累积
      // 最终 rank[0] 的值加一就是新节点的前置节点的排位
      // rank[0] 会在后面成为计算 span 值和 rank 值的基础
      // 第一次rank[i] = 0
      rank[i] = i == (max_level_ -1) ? 0 : rank[i+1];

      // 沿着前进指针遍历跳跃表
      // T_wrost = O(N^2), T_avg = O(N log N)
      // score 按照从小到大排
      // score 相同的时候，按照obj 从小到大排
      while (x->level_node[i].forward &&
             (x->level_node[i].forward->score < score ||
              // 比对分值
              (x->level_node[i].forward->score == score &&
               // 比对成员， T = O(N)
               (x->level_node[i].forward->obj.compare(obj)) < 0))) {

        // 记录沿途跨越了多少个节点
        rank[i] += x->level_node[i].span;

        // 移动至下一指针
        x = x->level_node[i].forward;
      }
      // 记录将要和新节点相连接的节点
      update[i] = x;
    }

    /* we assume the key is not already inside, since we allow duplicated
     * scores, and the re-insertion of score and redis object should never
     * happen since the caller of zslInsert() should test in the hash table
     * if the element is already inside or not.
     *
     * zslInsert() 的调用者会确保同分值且同成员的元素不会出现，
     * 所以这里不需要进一步进行检查，可以直接创建新元素。
     */

    // 获取一个随机值作为新节点的层数
    // T = O(N)
    level = get_random_level();

    // 如果新节点的层数比表中其他节点的层数都要大
    // 那么初始化表头节点中未使用的层，并将它们记录到 update 数组中
    // 将来也指向新节点
    if (level > max_level_) {

      // 初始化未使用层
      // T = O(1)
      for (i = max_level_; i < level; i++) {
        rank[i] = 0;
        update[i] = header_;
        update[i]->level_node[i].span = length_;
      }

      // 更新表中节点最大层数
      max_level_ = level;
    }

    // 创建新节点
    x = new SkipNode(score,obj, level);

    // 将前面记录的指针指向新节点，并做相应的设置
    // T = O(1)
    for (i = 0; i < level; i++) {

      // 设置新节点的 forward 指针
      x->level_node[i].forward = update[i]->level_node[i].forward;

      // 将沿途记录的各个节点的 forward 指针指向新节点
      update[i]->level_node[i].forward = x;

      /* update span covered by update[i] as x is inserted here */
      // 计算新节点跨越的节点数量
      x->level_node[i].span = update[i]->level_node[i].span - (rank[0] - rank[i]);

      // 更新新节点插入之后，沿途节点的 span 值
      // 其中的 +1 计算的是新节点
      update[i]->level_node[i].span = (rank[0] - rank[i]) + 1;
    }

    /* increment span for untouched levels */
    // 未接触的节点的 span 值也需要增一，这些节点直接从表头指向新节点
    // T = O(1)
    for (i = level; i < max_level_; i++) {
      update[i]->level_node[i].span++;
    }

    // 设置新节点的后退指针
    x->backward = (update[0] == header_) ? NULL : update[0];
    if (x->level_node[0].forward)
      x->level_node[0].forward->backward = x;
    else
      tail_ = x;

    // 跳跃表的节点计数增一
    length_++;

    return x;
  }

  int remove(double score, const std::string& obj)
  {
    SkipNode *update[SkiplistMaxLevel], *x;
    int i;

    // 遍历跳跃表，查找目标节点，并记录所有沿途节点
    // T_wrost = O(N^2), T_avg = O(N log N)
    x = header_;
    for (i = max_level_-1; i >= 0; i--) {

      // 遍历跳跃表的复杂度为 T_wrost = O(N), T_avg = O(log N)
      while (x->level_node[i].forward &&
             (x->level_node[i].forward->score < score ||
              // 比对分值
              (x->level_node[i].forward->score == score &&
               // 比对对象，T = O(N)
               (x->level_node[i].forward->obj.compare(obj)) < 0)))

        // 沿着前进指针移动
        x = x->level_node[i].forward;

      // 记录沿途节点
      update[i] = x;
    }

    /* We may have multiple elements with the same score, what we need
     * is to find the element with both the right score and object.
     *
     * 检查找到的元素 x ，只有在它的分值和对象都相同时，才将它删除。
     */
    x = x->level_node[0].forward;
    if (x && score == x->score && (x->obj.compare(obj) == 0)) {
      // T = O(1)
      remove(x, update);
      // T = O(1)
      delete x;
      return 1;
    } else {
      return 0; /* not found */
    }

    return 0; /* not found */
  }

  SkipNode * get_element_by_rank(unsigned long rank)
  {
    if(rank > length_)
      return nullptr;
    SkipNode *x = header_;
    while(rank--)
    {
      x =  x->level_node[0].forward;
    }
    return x;
  }

  // O(logN)的复杂度
  unsigned long get_rank(double score, const std::string& o) const {
    SkipNode *x;
    unsigned long rank = 0;
    int i;

    // 遍历整个跳跃表
    x = header_;
    for (i = max_level_-1; i >= 0; i--) {

      // 遍历节点并对比元素
      while (x->level_node[i].forward &&
             (x->level_node[i].forward->score < score ||
              // 比对分值
              (x->level_node[i].forward->score == score &&
               // 比对成员对象
               (x->level_node[i].forward->obj.compare(o)) <= 0))) {

        // 累积跨越的节点数量
        rank += x->level_node[i].span;

        // 沿着前进指针遍历跳跃表
        x = x->level_node[i].forward;
      }

      /* x might be equal to zsl->header, so test if obj is non-NULL */
      // 必须确保不仅分值相等，而且成员对象也要相等
      // T = O(N)
      if (x->score == score && x->obj.compare(o) == 0) {
        return rank;
      }
    }

    // 没找到
    return 0;
  }

  size_t size() const{
    return length_;
  }

  std::vector<SkipNode*> range(unsigned long start, unsigned long stop) const
  {
    if(start > length_ || stop > length_ || start > stop)
      return {};
    int len = stop + 1 - start;
    SkipNode * scan = header_->level_node[0].forward;
    while (start --)
    {
      scan = scan->level_node[0].forward;
    }
    std::vector<SkipNode*> res;
    while(len--)
    {
      res.push_back(scan);
      scan = scan->level_node[0].forward;
    }
    return res;
  }

  void remove(SkipNode *x, SkipNode **update) {
    int i;

    // 更新所有和被删除节点 x 有关的节点的指针，解除它们之间的关系
    // T = O(1)
    for (i = 0; i < max_level_; i++) {
      if (update[i]->level_node[i].forward == x) {
        update[i]->level_node[i].span += x->level_node[i].span - 1;
        update[i]->level_node[i].forward = x->level_node[i].forward;
      } else {
        update[i]->level_node[i].span -= 1;
      }
    }

    // 更新被删除节点 x 的前进和后退指针
    if (x->level_node[0].forward) {
      x->level_node[0].forward->backward = x->backward;
    } else {
      tail_ = x->backward;
    }

    // 更新跳跃表最大层数（只在被删除节点是跳跃表中最高的节点时才执行）
    // T = O(1)
    while(max_level_ > 1 && header_->level_node[max_level_-1].forward == NULL)
      max_level_--;

    // 跳跃表节点计数器减一
    length_--;
  }
  // 用来返回一个随机level，介于1 和 MAX_LEVEL之间
  // 使用幂等定律，越大的值生成概率越小。
  // 这里用来新建节点时生成的随机层数
  int get_random_level()
  {
    int level = 1;

    while ((random()&0xFFFF) < (SkipListP * 0xFFFF))
      level += 1;

    return (level<SkiplistMaxLevel) ? level : SkiplistMaxLevel;
  }

  SkipNode *header_;
  SkipNode *tail_;
  unsigned long length_; // 节点数目
  int max_level_; // 最大层数
};

using ZSkiplist = Skiplist<32>;
using ZSkipNode = Skiplist<32>::SkipNode;
