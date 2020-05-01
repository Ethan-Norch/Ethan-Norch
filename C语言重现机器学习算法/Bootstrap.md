### Bootstrap

Bootstrap又称自助法，一种有放回的抽样方法，是用小样本估计总体值的一种非参数方法。

![img](https://upload-images.jianshu.io/upload_images/1361150-2eb4ec3447748f54.png?imageMogr2/auto-orient/strip|imageView2/2/w/559)

Bootstraping: 名字来自成语“pull up by your own bootstraps”，意思是依靠你自己的资源，称为自助法，它是一种有放回的抽样方法，它是非参数统计中一种重要的估计统计量方差进而进行区间估计的统计方法。其核心思想和基本步骤如下：

- 采用重抽样技术从原始样本中抽取一定数量（自己给定）的样本，此过程允许重复抽样。
- 根据抽出的样本计算给定的统计量T。
- 重复上述N次（一般大于1000），得到N个统计量T。
- 计算上述N个统计量T的样本方差，得到统计量的方差。

### 例子

假设我们有两个金融资产X和Y，我们现在想要合理配置这两个资产，使得其资产组合的风险最小。也就是找到一个![[公式]](https://www.zhihu.com/equation?tex=%5Calpha+)，使得![[公式]](https://www.zhihu.com/equation?tex=Var%28%5Calpha+X%2B%281-%5Calpha%29Y%29)最小。这个问题几十年前马尔可维茨已经在其投资组合理论里给出了解答，最优的![[公式]](https://www.zhihu.com/equation?tex=%5Calpha)表达式如下：



![img](https://pic2.zhimg.com/80/v2-6304c35661c6669ab9febc490204c575_1440w.png)

但是现实生活中实际上我们并不知道![[公式]](https://www.zhihu.com/equation?tex=%5Csigma+_X%5E2),![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_Y%5E2)以及![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_%7BXY%7D)的值，故而只能通过X和Y的一系列样本对其进行估计。并用估计值![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma+_X%5E2%7D),![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_Y%5E2%7D)以及![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_%7BXY%7D%7D)代替![[公式]](https://www.zhihu.com/equation?tex=%5Csigma+_X%5E2),![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_Y%5E2)以及![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_%7BXY%7D)插入公式：





![img](https://pic1.zhimg.com/80/v2-4ef2e7257f52766695662eeec9f550b4_1440w.png)

所以我们唯一的任务就是合理地估计![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma+_X%5E2%7D),![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_Y%5E2%7D)以及![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_%7BXY%7D%7D)，传统方法中我们一般会考虑直接使用样本方差（sample variance）去估计![[公式]](https://www.zhihu.com/equation?tex=%5Csigma+_X%5E2),![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_Y%5E2)以及![[公式]](https://www.zhihu.com/equation?tex=%5Csigma_%7BXY%7D)的值，**然而自从有了Bootstrap之后，我们有了另一种方法与途径，可以更好地去做估计总体的分布特性，即不仅可以估计**![[公式]](https://www.zhihu.com/equation?tex=%5Calpha%0A)**，还可以估计**![[公式]](https://www.zhihu.com/equation?tex=%5Calpha%0A)**的方差、中位数等值。**

## Bootstrap步骤：

\1. 在原有的样本中通过重抽样抽取一定数量（比如100）的新样本，重抽样（Re-sample）的意思就是有放回的抽取，即一个数据有可以被重复抽取超过一次。

\2. 基于产生的新样本，计算我们需要估计的统计量。

在这例子中，我们需要估计的统计量是![[公式]](https://www.zhihu.com/equation?tex=%5Calpha%0A)，那么我们就需要基于新样本的计算样本方差、协方差的值作为![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma+_X%5E2%7D),![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_Y%5E2%7D)以及![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Csigma_%7BXY%7D%7D)，然后通过上面公式算出一个![[公式]](https://www.zhihu.com/equation?tex=%5Chat%7B%5Calpha%7D)


\3. 重复上述步骤n次（一般是n>1000次）。

在这个例子中，通过n次（假设n=1000），我们就可以得到1000个![[公式]](https://www.zhihu.com/equation?tex=%5Calpha_i)。也就是![[公式]](https://www.zhihu.com/equation?tex=%5Calpha_1%2C%5Calpha_2%2C%5Ccdots%2C%5Calpha_%7B1000%7D)。

\4. 最后，我们可以计算被估计量的均值和方差（不用关注最后的具体数值，这与原本的样本有关）：

![img](https://pic3.zhimg.com/80/v2-41aa578ffb3a17dd472ca74828603c46_1440w.png)

![img](https://pic1.zhimg.com/80/v2-46487494dd8258db1aec0c24e5b0f64c_1440w.png)

