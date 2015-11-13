/*
https://community.topcoder.com/tc?module=ProblemDetail&rd=16551&pm=14070

Limak is a big grizzly bear. He is now going to destroy an entire forest.


Limak's forest is a rectangular grid that consists of W columns by H rows of
cells. At the beginning a single tree grows in each cell. The forest is aligned
with the major compass directions: row numbers increase towards the South and
column numbers increase towards the East.


Limak will destroy the forest by pushing some of the trees. Whenever Limak
pushes a tree, the tree will fall down and remain lying both in the current
cell and in the next cell in the direction in which it was pushed. For example,
if Limak pushes the tree that grows in the cell (r,c) southwards, he will
obtain a toppled tree that lies in the cells (r,c) and (r+1,c).


When pushing the trees, Limak always follows a few rules:

He only pushes trees in two directions: either southwards or eastwards.
He will never push a tree in a way that would cause it to fall out of the forest. For example, he will never push a tree in the last column eastwards.
He will never push a tree in a way that would produce two fallen trees lying on the same cell.


There is a single letter written on each of the trees. Each of these letters is
either S or E (representing South and East, respectively). When pushing a tree,
Limak will prefer the direction that is written on the tree. For example, if a
tree has the letter S, Limak will push it southwards if possible.



Limak is going to visit each cell in the forest exactly once, in row major
order. I.e., first he will visit all the cells in the first row from left to
right, then the cells in the second row from left to right, and so on. In each
cell he will act according to the following algorithm:



Is there a fallen tree in the current cell? If yes, there is no room here to do anything, so I'll just move to the next cell.
Can I push the tree in the direction that is given by the letter written on the tree? If yes, I'll do so and move to the next cell.
Can I push the tree in the other direction? If yes, I'll do so and move to the next cell.
I'll move to the next cell without pushing the tree.


See Example 0 for a sample execution of Limak's algorithm.



You are given the ints W and H. There are 2^(W*H) different forests with these
dimensions. (Different forests have different assignments of letters S and E to
the trees.) For each of these forests, compute the number of trees Limak would
topple. Return the sum of those 2^(W*H) numbers, modulo MOD.

 
Definition

Class:  BearDestroysDiv2
Method: sumUp
Parameters: int, int, int
Returns:    int
Method signature:   int sumUp(int W, int H, int MOD)
(be sure your method is public)


Constraints
-   W will be between 1 and 7, inclusive.
-   H will be between 1 and 40, inclusive.
-   MOD will be between 3 and 10^9, inclusive.
-   MOD will be prime.
 
Examples
0)

4
3
999999937
Returns: 24064
There are 2^(4*3) = 2^12 = 4096 different forests with W=4 columns and H=3 rows. One of those forests looks as follows:
SEEE
ESSS
EESS
When destroying this forest, Limak will push five trees. In the scheme below,
the final locations of the toppled trees are shown using the numbers 1 through
5. The trees are numbered in the order in which Limak pushed them. The two
cells that do not contain a fallen tree at the end are denoted by underscores.
1223
1453
_45_
It can be shown that for these dimensions there are exactly 512 forests in
which Limak would topple exactly 5 trees. In each of the remaining (4096-512)
forests Limak would topple 6 trees. Thus, the return value is 512 * 5 +
(4096-512) * 6.
1)

3
4
999999937
Returns: 24576
For these dimensions of the forest Limak will always topple exactly 6 trees.
The return value is 6 * 2^12.
2)

2
20
584794877
Returns: 190795689
For these dimensions of the forest Limak will always topple exactly 20 trees.
The return value is (20 * 2^40) modulo MOD.
3)

5
10
3
Returns: 2
4)

1
1
19
Returns: 0
5)

7
40
312880987
Returns: 256117818
*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec)
{
    os << "{ ";
    if(vec.size() != 0)
    {
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    }
    os << "}";
    return os;
}


int topple_tree(int w, int h, int i, int j, std::vector<char>& forest)
{
    int idx = i * w + j;
    if(forest[idx] == 'T') return 0;

    int trees_toppled = 0;
    if(forest[idx] == 'E')
    {
        if(j < w-1 && forest[idx+1] != 'T')
        {
            forest[idx] = 'T';
            forest[idx+1] = 'T';
            trees_toppled = 1;
        }
        else if(i < h-1 && forest[idx+w] != 'T')
        {
            forest[idx] = 'T';
            forest[idx+w] = 'T';
            trees_toppled = 1;
        }
    }
    else if(forest[idx] == 'S')
    {
        if(i < h-1 && forest[idx+w] != 'T')
        {
            forest[idx] = 'T';
            forest[idx+w] = 'T';
            trees_toppled = 1;
        }
        else if(j < w-1 && forest[idx+1] != 'T')
        {
            forest[idx] = 'T';
            forest[idx+1] = 'T';
            trees_toppled = 1;
        }
    }

    return trees_toppled;
}

int count_trees_in_forest(std::vector<char> forest, int w, int h)
{
    int toppled_trees = 0;
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            toppled_trees += topple_tree(w, h, i, j, forest);
        }
    }
    return toppled_trees;
}

void count_toppled_trees(std::vector<char>& forest, std::size_t i, int w, int h, long int& toppled_trees)
{
    if(i == forest.size())
    {
        toppled_trees += count_trees_in_forest(forest, w, h);
    }
    else
    {
        for(int v : {'E', 'S'})
        {
            forest[i] = v;
            count_toppled_trees(forest, i+1, w, h, toppled_trees);
        }
    }
}

int sum_up(int W, int H, int MOD)
{
    std::vector<char> forest;

    long int num_forests = W * H;
    forest.reserve(num_forests);
    forest.resize(num_forests);

    long int count = 0;
    count_toppled_trees(forest, 0, W, H, count);
    std::cout << "got a count of: " << count << std::endl;
    return count % MOD;
}

#include <bits/stdc++.h>
using namespace std;

int f[50][(1<<10)], MOD, p[10000];

class BearDestroysDiv2
{
  int N, M, MOD;
  int getbit(int a, int j)
  {
    return ((a>>(j-1))&1);
  }
  int batbit(int a, int j)
  {
    return (a|(1<<(j-1)));
  }
  int dp(int r, int mask)
  {
    if (r==M+1) return 0;
    if (f[r][mask]!=-1)
    {
        std::cout << "Reusing r: " << r << ", mask: " << mask << std::endl;
        return f[r][mask];
    }
    int res = 0;
    for(int b=0; b<(1<<N); b++)
    {
      int cnt = 0, nmask = 0;
      bool ar = 0;
      for(int k=1; k<=N; k++)
      {
        if (ar)
        {
          ar=0;
          continue;
        }
        int i = getbit(mask,k), j = getbit(b,k);
        if (i==1) continue;
        if (r<M&&(j==0||(j==1&&(k==N||getbit(mask,k+1)==1))))
        {
          nmask=batbit(nmask,k);
          //res+=(p[(M-r)*N+N-k]); res%=MOD; 
          cnt++;
          continue;
        }
        if (k<N&&getbit(mask,k+1)==0)
        {
          ar=1;
          //res+=(p[(M-r)*N+N-k]); res%=MOD;
          cnt++;
        }
      }
      res+=((cnt*1ll*p[(M-r)*N])%MOD); res%=MOD;
      int t = dp(r+1,nmask);
      res+=t; res%=MOD;
    }
    f[r][mask]=res; return res;
  }
  public:
  int sumUp(int W, int H, int M)
  {
    MOD=M;
    p[0]=1;
    for(int i=1; i<=W*H; i++)
      p[i]=(p[i-1]*2ll)%MOD;
    this->N=W; this->M=H;
    memset(f,255,sizeof(f));
    int res = dp(1,0);
    return res;
  }
};



int main(int argc, char* argv[])
{
    long w = 0, h = 0, mod = 0;
    if(argc > 3)
    {
        w = std::stol(argv[1]);
        h = std::stol(argv[2]);
        mod = std::stol(argv[3]);
    }
    std::cout << "w = " << w << ", h = " << h << ", mod = " << mod << std::endl;
    BearDestroysDiv2 bdd;
    std::cout << bdd.sumUp(w, h, mod) << std::endl;
}
