# Sudoku2

Software Engineering, BUAA 结对项目

---

## 使用说明

**Sudoku** is a worldwide prevailing puzzle game.<br>
The objective is to fill a 9\*9 grid with digits so that each column, each row, and each of the nine 3\*3 subgrids that compose the grid contains all of the digits from 1 to 9.<br>
To start a new game, click **Game** at the top of the window, click **New Game** and select a mode from Easy, Normal and Hard.<br>
During the play, to fill in digits, click empty blue buttons on the left, which will be marked by yellow, to select a cell, and click fuchsin buttons with digits on the right. <br>

 - To erase your answers, select a digit and click **Erase**.
 - To check or submit your current answer, click **Check**.
 - To locate cells of a specific number, click a digit on the right and click **Track**.
 - To see the answer of a cell, select it and click **Tip**. The result of the current game will not be admitted to the leaderboard if you have used any tips.
 - To see the leaderboard, click **Game** and click **Leaderboard**.
 - To filter possibilities of a cell, select it and click **Filter**, which returns a possible solution for the cell at each click.
 - To learn more about our work and us, click **About**. 

## 实现功能

部分引用自[结对项目-数独程序扩展](http://www.cnblogs.com/jiel/p/7604111.html)

### -m 参数设定难度

命令行中使用-n和-m参数分别控制生成数独游戏初始盘的数量与难度等级，

> sudoku.exe -n [number] -m [mode]

**-n和-m参数的限制范围不同，具体约定如下：**

 - [number]的范围限定为1 - 10000。
 - [mode]的范围限定为1 - 3，不同的数字代表了数独游戏的难度级别，如下表所示：

编号 | 级别
|:-:|:-:|
1	| 简单
2	| 入门
3	| 困难

例如下述命令将生成**20个简单级别**的数独游戏初始棋盘至文件```sudoku.txt```中，挖空的地方用0表示：

> sudoku.exe -n 20 -m 1

    9 0 8 0 6 0 1 2 0
    2 0 7 4 0 1 9 0 8
    1 4 6 0 2 0 3 5 0
    0 1 2 0 7 0 5 0 3
    0 7 3 0 1 0 4 8 2
    4 8 0 0 0 5 6 0 1
    7 0 4 5 9 0 8 1 6
    0 0 0 7 4 6 2 0 0
    3 0 5 0 8 0 7 0 9

    9 0 0 8 0 0 4 0 0
    ……
    
### -r 参数设定挖空数量

命令行中使用-n参数控制生成数独游戏初始盘的数量，-r参数控制生成数独游戏初始盘中挖空的数量范围，使用-u参数控制生成数独游戏初始盘的解必须唯一，

> sudoku.exe -n [number] -r [lower]~[upper] -u

**-r参数的范围限制如下：**

 - [lower] 的值最小为20，
 - [upper] 的值最大为55，
 - [upper] >= [lower]。

如果命令行中有-u参数，则生成的数独游戏初始盘的解必须唯一；否则，则对解的数量不做限制。

**注意：** -m参数不与-r和-u参数同时出现，如果同时出现则提示参数的正确用法。

例如下述命令将生成20个挖空数在20到55之间的数独游戏初始盘至文件```sudoku.txt```中，

> sudoku.exe -n 20 -r 20~55

下述命令将生成20个挖空数在20到55之间并且解唯一的数独游戏初始盘至文件```sudoku.txt```中，

> sudoku.exe -n 20 -r 20~55 -u
