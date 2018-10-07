# THU2018 1-3-3 ⑨的完美文本编辑器

## 解题思路
string
Bidirectional list(for easier reverse operation)

## 提交
- 1.
操作: 用string简单实现算法;
结果: 50%测试通过前三个, 其余均超时, 效率待优化

## 黑箱测试
1. 效率与[reverse]操作非常相关, 约1300-1600ms; 数组翻转开销过大, 尝试用其他不同的数据结构来处理数据;
2. 效率与printText相关, 约20-100ms;

## 尝试用双向链表实现复杂度低的翻转操作
   printText的方向问题已解决，只要链表节点两端正确指向上下节点， 不论方向正误与否， 只有当光标移动到这里是进行一次验证， 不符合就做个翻转，就能正确找到链表的方向；
    但是用指针实现链表的话，判断Lcursor和Rcursor的左右相对位置较复杂，需要做遍历；(解决：用int relativePos代替，光标做移动或其他操作时判断并校正relativePos的值；）

## 提交
- 2.
操作：实现上述双向链表，实现复杂度较低的reverse操作；
结果：50% 只过了2个， 其余均Runtime Error (signal 6), 出现不明原因异常退出程序，待debug;
不想做了，心态炸了。

- 3.
操作：修复提交2中的bug：Myerase函数中的参数错了；
结果：50% 90% 全过，worst case 18 time 668ms;
效率待优化，很多细节有很大优化空间；

- 4.
操作：去掉debug用的assert
结果：worst case 18 time 636ms
懒得优化了
