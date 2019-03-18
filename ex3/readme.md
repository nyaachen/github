# 斗地主

### 整体描述
---
本次题目应该属于某个大型项目的一部分，因此适宜使用系统性的方法来开发。

---
### 需求分析
---
- 程序应该有一个通用的牌组打印程序，按照牌从大到小的顺序进行排列。
- 程序一能够实现根据自己的手牌和别人的出牌来选出一组牌打牌。
- 第二个程序需要能给定一组手牌，选出一个合格的组合。
- 同时第二个程序需要复用第一个程序来执行任务。


---
### 模块设计
---
#### 对扑克牌的表示格式
>	每组手牌只包含有限的15种手牌，即 3 4 5 6 7 8 9 10 J Q K A 2 joker JOKER  
对于3-2，每种牌最多有4张；对于joker和JOKER，每种牌最多有一张。
因此，存储一副卡牌可以用所具有的卡牌的类型和卡牌数量的数值来表示。  
例如：对于卡牌 7 7 7 9 9 ,可以描述为3张7和2张9  
显然，手牌的机器内表示是一个抽象的线性表数据结构

```
ADT Card {
	data:
		Cardtype; 表示这张牌的类型
	option:
		比较两张牌的大小
		输入与输出单张卡牌
}



ADT Cards {
	data:
		LineList(Card, count);
	option:
		addCard(Cards) 添加一张（组）卡牌
		subCards 检查另一组卡牌是否是当前卡牌的子集的操作
		subCard(Cards) 取出一张（组）卡牌
		countCard 返回卡牌数量
}
```

---
#### 判断手牌能否比过指定牌型
>	给定某种特定的手牌，和别人出过的手牌，选择一个正确的牌型进行应对。
整体思路如下：
>	1.	判断别人出的牌是否是特殊牌型（指炸弹），如果是，跳到步骤`5`
>	-	选择对应牌型的检查比较函数，获得比较结果
>	-	如果获得的结果为真，返回对应的牌型
>	-	检查可行的特殊牌型，如有，返回结果；否则返回要不起。
>	-	检查是否有更大的特殊牌型，如有，返回结果；否则返回要不起。
></ol>
>
>根据这个框架，我们可能还需要一些辅助性的代码


```
bool cmpCards(myCards, targetCards, &resultCards) {
	if (!special_Cards(targetCards)) {	// 对应1
		cardtype = find_cardtype(targetCards);
		bool retcode;
		switch (cardtype) {	// 对应2
			case Cards_single:
				retcode = bigger_than_single(myCards, targetCards, resultCards);
			...

		}
		if (retcode) return retcode;	// 对应3
		else return find_a_bomb(myCards, resultCards);	// 对应4
	}
	else {
		return bigger_than_bomb(myCards, targetCards, resultCards);	// 对应5
	}
}
```

---
#### 实现自动对局
>要完成自动对局，首先要完成一个在自己先手出牌时候选出一副牌的函数。
这个函数大体的算法是这样的
1.	判断自己手上是否没有特殊牌型，如果没有，跳转到3
-	按照特定的实现选出一副特殊牌型，返回
-	选择一张单张，返回
></ol>
>
>可见，除了上面已经实现的函数之外，还需要一个策略函数来解决出牌策略优化。

---

### 代码与实现

在代码实现上， 程序采用C++面向对象进行实现

首先实现卡牌的机内表示
