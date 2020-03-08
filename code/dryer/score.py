import pandas as pd
import string

weight_file = pd.read_csv('word_weight.csv', usecols=[0, 11])
weight = dict(
    zip(weight_file["word"].tolist(), weight_file["score"].tolist())
)

review_file = pd.read_csv(u'reviews.csv', usecols=[0, 4], encoding="gb18030")
reviews = review_file["review_body"].tolist()
for r in reviews[0:3]:

    for word in r.split(" "):
        word = word.strip(string.punctuation)
        word = word.rstrip(string.punctuation)

