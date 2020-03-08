import numpy as np

statistic = {}


def cal(rate):
    # rate in range(5)
    f = open(str(rate + 1) + ".out")
    f.readline()  # total word number

    global statistic
    line = f.readline().strip('\n')
    while line:
        word = line.split('\t')  # ['1', 'dryer', '62', '1.37472']
        # print(word)

        if word[1] not in statistic:
            statistic[word[1]] = [0, 0, 0, 0, 0]
        statistic[word[1]][rate] = float(word[3])

        line = f.readline().strip('\n')

    f.close()
    return


def score(prob):
    for rate in prob.values():
        rate.extend(np.array(rate) / sum(rate))
        rate.append(np.dot(np.array(rate[5:10]), np.array([1, 2, 3, 4, 5])))


def table_head():
    title = "word, "
    for i in range(5):
        title += "frequency in " + str(i + 1) + ", "
    for i in range(5):
        title += "probability in " + str(i + 1) + ", "
    title += "score"
    return title


for i in range(5):
    cal(i)
score(statistic)

f = open("testout.csv", mode='w')

print(table_head(), file=f)
for key, value in statistic.items():
    print('{key}, {value}'.format(
        key=key, value=", ".join(str(i) for i in value)), file=f)
