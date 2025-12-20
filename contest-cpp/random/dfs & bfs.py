#lc2059 minimum operations to convert number
class Solution:
#刚拿到这题找不出什么规律，要我们求最小运算次数，加之这个数据范围很小，无权最短路...暴力... 嘶~ BFS ？！

#以前自己做题经常爱用 DFS，因为递归代码一般会少一些。
# 但是 DFS 与 BFS 在寻找路径最不同的一点是，DFS 是一条路走到黑，它适合用于 「是否存在一条路径」
# 而 BFS 是影分身，每次影分身都会在原基础上走一步，适合用于 「是否存在一条最短路径」。

#明白上面两点区别，便可顺利通过。

    def minimumOperations(self, nums: List[int], start: int, goal: int) -> int:
        if start < 0 or start > 1000 or start == goal:
            return start == goal
        q = deque([start])
        vis = set([start])
        step = 0

        while q:
            size = len(q)
            while size:
                cur = q.popleft()
                for x in nums:
                    compute = (cur + x, cur - x, cur ^ x)
                    for y in compute:
                        if y == goal:
                            return step + 1
                        if 0 <= y <= 1000 and y not in vis:
                            q.append(y)
                            vis.add(y)
                size -= 1
            step += 1
        
        return -1