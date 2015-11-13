# Does the next word start next line?
# 1) Subproblem: suffixes words[i:]
# 2) Guess: all possible words after the first word. Where to start the next line?
#    # of choices <= n-i = O(n)
# 3) Recurrence: DP(i). min(DP(j) + badness(i, j) for j in range(i+1, n+1))
# 4) topological order: i = n, n-1, ... 0. Total time: O(n^2)
# 5) Original problem: DP(0)


text = """Your password for account "ayeganov" expires in 14 day(s). Please
change the password as soon as possible to prevent further logon problems. You
can change your Password by pressing CONTROL, ALT, DELETE on your keyboard and
choosing the option for "Change Password". Remember you must choose a password
that you have not used before and it must be a minimum of 8 characters in
length. This feature will only work if you are connected to the zollmed network
or connected by VPN."""

words = text.split()

test_words = ['Aleks', 'likes', 'to', 'program', 'and', 'learn']#, 'new', 'things']
line_width = 10


def badness(i, j, words):
    print(i, j)
    cut = words[i:j]
    print(cut)
    total_width = sum(len(word) for word in cut) + len(cut) - 1
    width_diff = line_width - total_width
    return float("inf") if width_diff < 0 else width_diff ** 3


memo = {}


import pudb

def dp(i, words):
    if i in memo:
        return memo[i]
    if i == len(words):
        return badness(i, i + 1, words)

    res = min((badness(i, j, words) + dp(j, words) for j in range(i + 1, len(words) + 1)))
    memo[i] = res
    print(i)
    return res


def main():
#    pudb.set_trace()
    print("min cost is: {0}".format(dp(0, test_words)))
    print(memo)


if __name__ == "__main__":
    main()
