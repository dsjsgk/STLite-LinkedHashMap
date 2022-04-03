# STLite-LinkedHashMap

### * 实现要求


​    *     实现的LinkedHashMap要求与HashMap基本相同，但是在HashMap的基础上要求实现一些新的功能


​    *     实现向数据结构插入形如(Key,Value) 的元素对 (HashMap的基本功能)


​    *     实现在数据结构中查询某个特定的 Key 所对应的 Value (HashMap的基本功能)


​    *     实现按照插入顺序访问插入的元素 (新增的功能)


​    *     所有实现的功能都要求均摊复杂度是 O(1)，所以不能在Map的基础上实现本次大作业 (我们会进行压力测试来阻止这种行为，如果通过测试的代码在Code Review阶段被发现存在这种行为将会被酌情扣分)


​    *     具体需要实现的接口见下发文件中的 `linked_hashmap.hpp`



### * 分数构成

####  80% OJ分数 + 20% CodeReview



### * 截止日期

#### 4.24

### 请注意，下发的测试数据与OJ上的数据并不完全相同，若想获得完整的测试数据，可以自己用`std::unordered_map`实现一个`linked_hashmap_std.hpp`,并且取消测试数据中的注释！
