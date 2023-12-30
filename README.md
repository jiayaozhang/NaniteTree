# NaniteTree_Imposter2Mesh_Simplification



## Part one Implementation ( TODO Hiko )


## Part two Tech details 

⽅法⼀ Lindstrom-Turk Cost and Placement Strategy

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/f99489a6-772c-421c-bc7f-c5a15ec53bac)

传统智慧认为，在简化多边形模型时，必须保留并使⽤原始模型的信息才能产⽣⾼质量的简化模型。
我们证明，在执⾏模型的局部变化时，可以不需要⽐较原始⼏何信息就可以产⽣优秀的简化模型。我
们使⽤边缩减来执⾏简化，其他⽅法也采⽤了这种⽅法。我们选择新顶点的位置，以保持模型的原始
体积，并最⼩化由移动的三⻆形所围成的四⾯体的每个三⻆形的体积变化。我们还保持边界附近的表
⾯积，并最⼩化每个三⻆形的⾯积变化。计算边缩减优先级和新顶点的位置仅需要中间模型中的⾯连
接和顶点位置。这种⽅法具有内存效率，可以简化⾮常⼤的多边形模型，⽽且速度也很快。此外，使
⽤此技术创建的简化模型在平均⼏何误差⽅⾯与许多其他已发表的简化⽅法相⽐具有优势。

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/25c5f891-d4d4-4d3b-944d-a668cbf9af9c)

我们使⽤边折叠作为⼏何简化的⽅法，之前的⼀些研究者也使⽤了这种⽅法。这种⽅法选择⼀条边并
⽤⼀个单独的顶点代替它（图2）。这将删除⼀个顶点、三条边和两个⾯。边折叠操作很有吸引⼒，因
为它允许新顶点以有助于保持原始表⾯位置和形状的⽅式放置。它也⽐顶点或⾯的删除更原⼦化，并
不需要调⽤三⻆剖分算法。简化⽅法使⽤边折叠有两个关键决定：1）边折叠创建的新顶点的位置，
2）要折叠的边的排序（边优先级）。我们使⽤体积和表⾯积信息来做出这两个决策。我们限制新顶点
的放置，以使封闭模型的体积不被改变。如果新顶点靠近模型的边界，则我们还保留边缘附近的表⾯
积。通常这两个限制并不能完全确定新顶点的位置，因此我们对其他⼏何属性进⾏优化。我们最⼩化
通过操作移动的三⻆形所扫过的体积，最⼩化边界边扫过的⾯积，最后尝试⽣成形状良好的三⻆形，
如果顶点仍然不完全确定。我们的⽅法通过将每个限制描述为⼀个或多个平⾯来统⼀这些不同的限
制，在这些平⾯中，新顶点必须位于其中之⼀。我们使⽤每个三⻆形的体积和⾯积差异来确定边折叠
的优先级。
总结：选择⼀个指定边缘折叠成本的度量，并选择替换边缘的顶点v的位置。
该策略的主要特点是在每个步骤中，简化后的表⾯⽹格不会与原始表⾯⽹格（或以前步骤的表⾯⽹
格）进⾏⽐较，因此⽆需保留额外信息，例如原始表⾯⽹格或局部更改的历史记录。因此，这种⽅法
被称为⽆记忆简化。
在每个步骤中，所有剩余的边都是可能的合并候选项，选择成本最低的⼀条。合并边的成本由替换它
的顶点位置确定。替换顶点位置是通过解⼀个具有3个线性独⽴线性等式约束条件的系统来计算的。每
个约束条件都是在先前计算的约束条件下最⼩化⼆次⽬标函数得到的。存在多个可能的候选约束条
件，每个都按照重要性顺序考虑。候选约束条件可能与先前接受的约束条件不兼容，在这种情况下，
它将被拒绝，考虑下⼀个约束条件。⼀旦接受了3个约束条件，该系统就会被求解出顶点位置。第⼀个
被考虑的约束条件保留了表⾯⽹格边界的形状（如果边缘剖⾯具有边界边）。接下来的约束条件保留
了表⾯⽹格的总体积。如果需要，下⼀个约束条件将优化体积和边界形状的局部更改。最后，如果需
要约束条件（因为先前计算的条件不兼容），则添加第三个（也是最后⼀个）约束条件，以⽀持等边
三⻆形⽽不是细⻓三⻆形。成本是形状、体积和边界优化项的加权和，其中⽤⼾为每个项指定了单位
权重因⼦。局部更改是针对每个边独⽴计算的，仅使⽤当前在边将要被合并时与之相邻的三⻆形，即
在所有先前的合并之后。因此，最⼩局部更改的传递路径最终产⽣的全局更改与绝对最⼩值相当接
近。

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/4cf10168-d35f-4a16-a2ea-c3e55280a763)


⽅法⼆ Garland-Heckbert Cost and Placement Strategy

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/f0e28c62-3a68-4657-9517-0873c8a508bb)

与 Lindstrom-Turk 策略类似，Garland-Heckbert 策略中引⼊了近似距离原始⽹格的⽅法，通过为每
个顶点分配⼆次矩阵来实现。在经典版本中，每个顶点 v 都对应⼀个⼆次矩阵 Q，该矩阵编码了任何
点 p 到 v 的相邻⾯的总平⽅距离，该距离由矩阵乘积 p′Qp 给出。在每个步骤中，选择使折叠成本
最⼩的边进⾏折叠操作。折叠边的成本计算是通过最⼩化误差函数 p′Qp 来计算的，其中 Q 是边端
点的组合⼆次矩阵，p 是使成本最⼩的点（即决策变量）。使⽬标函数最⼩的点被选择作为新的放置
点。由于误差函数是⼆次的，因此可以通过计算梯度并将其等于零来找到其最⼩值。如果由于奇异性
⽽失败，则在边缘上找到最优点和成本。在放置新顶点后，新的⼆次矩阵被分配给它，⽅法是简单地
将已折叠边的两个端点的⼆次矩阵相加。为了尽可能保留⽹格的尖锐边界，还会将垂直于相邻⾯的伪
⾯添加到边界顶点的⼆次矩阵中。Trettner 和 Kobbelt 提出了 Garland-Heckbert 的扩展，他们提出
了概率⼆次矩阵的概念。在这种新的⽅法中，能量最⼩化不再使⽤与输⼊平⾯或多边形的距离，⽽是
通过在输⼊中引⼊⾼斯噪声（顶点位置和⾯法线）来使输⼊⼏何图形不确定。这种⽅差⾃然会破坏结
果的紧密性，但另⼀⽅⾯，它能够创建更均匀的三⻆形，并且该⽅法对噪声更容忍，同时仍然保持特
征敏感性。

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/6a28c162-41a5-4b4b-b9b5-b9553a871cf5)


⽅法三 Cost Strategy Policies

算法使⽤的成本策略是通过三个策略选择的：GetPlacement，GetCost和Filter。 GetPlacement策略
被调⽤以计算半边折叠后剩余顶点的新位置。它返回⼀个可选值，如果不应折叠边，则可能不存在。
GetCost策略被调⽤以计算折叠边的成本。该策略使⽤放置来计算成本（这是⼀个错误度量），并确
定边的排序。 算法维护⼀个内部数据结构（可变优先队列），它允许每个边以递增成本顺序进⾏处
理。这样的数据结构需要⼀些每个边的附加信息，例如边的成本。如果每个边的附加信息记录占⽤N字
节的存储空间，则简化1百万个边的表⾯⽹格（正常⼤⼩）需要1百万次N字节的额外存储。因此，为了
最⼩化简化表⾯⽹格所需的额外内存量，仅将成本附加到每个边缘，⽽不附加其他任何东西。 但这是
⼀个权衡：折叠的成本是放置（剩余顶点选择的新位置）的函数，因此在为每个边调⽤GetCost之前，
还必须调⽤GetPlacement以获取成本函数的放置参数。但是，该放置是⼀个3D点，不附加到每个边
缘，因为这会轻松将额外存储要求增加三倍。⼀⽅⾯，这极⼤地节省了内存，但另⼀⽅⾯是⼀种处理
浪费，因为当边缘实际上折叠时，还必须再次调⽤GetPlacement以知道将剩余顶点移动到哪⾥。 早期
的原型表明，将放置附加到边缘，从⽽避免了折叠后⼀个冗余的放置函数调⽤，对总运⾏时间的影响
很⼩。这是因为每个边缘的成本不仅仅计算⼀次，⽽且在过程中会多次更改，因此必须多次调⽤放置
函数。缓存放置只能避免最后⼀个调⽤，即当边缘折叠时，⽽不能避免所有之前需要的调⽤，这些调
⽤是必需的，因为放置（和成本）会改变。 最后，我们解释了PlacementFilter策略。虽然成本是优先
队列中使⽤的标量，但可能会有其他标准来决定是否执⾏边缘折叠。虽然这样的标准可以很容易地集
成到成本函数中，例如将成本设置为⽆穷⼤，以便不被视为折叠的候选对象，但我们仅在下⼀个要折
叠的边缘时测试标准。如果计算标准是昂贵的，例如当我们检查简化的⽹格是否在输⼊⽹格的公差包
络中时，这使得⽹格简化更快。
核⼼点：检查⼀个放置是否会翻转候选边的两个顶点星形图中的⼀个⾯的法线。如果会翻转法线，则
拒绝该放置并返回 boost::none

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/3a4c10eb-5339-43b4-9618-127dcf6a32ec)

## Part Three 如何封装Houdini HDK

1. 创建dso⽂件夹，前往C:\Users\你的电脑名\Documents\houdini19.0创建⼀个dso⽂件夹
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/7f0dfb07-dc27-4762-87fd-b4445d0c6413)

2. 设置houdini.env，在⾥⾯写上HOUDINI_DSO_PATH = $HOME\houdini19.0\dso;& 这句话是保证
你⽣成dll⾃动分配到dso⽂件夹⾥⾯

![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/f9a16030-897f-47ce-863a-287991bda758)

3. 书写CMakeLists⽂件内容，官⽹有样例 HDK: Compiling HDK Code (sidefx.com)
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/a3407cf2-dbeb-452e-a7dd-e2963f6f4806)

4. 调⽤CMakeLists⽂件，在houdini中找到Command Line Tools
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/577ebc1c-ec7f-4ecd-a8c2-30b58392e249)

5. 然后选择NaniteSimpilification右键，重新⽣成
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/09d6e035-c1a2-4e00-b3cc-38148905e474)

6. 下⽅显⽰这些，即代表成功
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/0ace8999-4d5b-4c04-9532-775711282444)

7. dso⽂件夹可以看到这些⽂件
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/ac1a6df4-ddad-4071-b35a-cda7ca10b2c6)

8. 打开Houdini，创建⼀个Geometry节点，进⼊节点内部，按tab键，找到Coustom就可以看到刚才
⽣成的节点。
![image](https://github.com/jiayaozhang/NaniteTree_Imposter2Mesh_Simplification/assets/38579506/f6b8d167-3008-4fc9-acc5-b85d71341f6f)



