import csv
import numpy as np
import pandas as pd

line_num = int(input("The number of line\n"))

random_text = np.random.rand(line_num)*20 - 10
random_text = np.around(random_text, 3)
random_text = random_text.tolist()

for i in range(len(random_text)):
    if random_text[i]>=0:
        random_text[i] = '+'+str(random_text[i])
        if len(random_text[i])<6:
            random_text[i] = random_text[i]+'0'*(6-len(random_text[i]))
        
    else:
        random_text[i] = str(random_text[i])
        if len(random_text[i])<6:
            random_text[i] = random_text[i]+'0'*(6-len(random_text[i]))
        
res = []
for i in range(3):
    random.shuffle(random_text)
    res.append(random_text)
data=pd.DataFrame(res).T


data.to_csv('test_file', sep=' ', index=False,header=False,quoting=csv.QUOTE_NONE,escapechar=' ')
