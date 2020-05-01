## C语言重现机器学习算法



C语言重现Bootsrap、Backpropagation、KNN、LVQ、MM-LogisticRegression、MultivariateLinearRegression、NaiveBayes、Perception、RegressionTree、SG、SimpleLinearRegression



数据说明：重现机器学习中所用的数据大多都是由随机种子形成的，结果不具有参考性。



### Bootstrap

通过如何分配资产X、Y实现

### Backpropagation

人为输入神经层数，以及每一个层的神经元数，随机种子生成数据。

### KNN

训练集是王者荣耀20局数据，分析当下情况中召唤师应该做什么。

### MMLogisticRegression

随机种子生成数据

MultivariateLinearRegression、SimpleLinearRegression

人为输入训练集

NaiveBayes

分析是否参加聚会（文本训练）

Perception

程序内自定训练集

RegressionTree

对连续型数据进行二叉树分类，人为输入数据、分叉数

SG

两层模型，第一层模型是KNN、Perception，第二层聚合模型是LogisticRegression，由于算法大小影响学习速度，进行二分类学习（可做多分类学习）。