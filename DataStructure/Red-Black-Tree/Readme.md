# 红黑树




### 插入
* 插入时需要调整的三种情况：
 * 情况1: z的叔叔y是红色的；
 * 情况2: z的叔叔y是黑色的 && z是右孩子；
 * 情况3: z的叔叔y是黑色的 && z是左孩子。




### 删除

* 删除时需要调整的四种情况：
  * 情况1: x的兄弟w是红色的；
  * 情况2: x的兄弟w是黑色的 && w的两个孩子都是黑色的；
  * 情况3: x的兄弟w是黑色的 && w的左孩子红色、右孩子黑色；
  * 情况4: x的兄弟w是黑色的 && w的右孩子黑色。