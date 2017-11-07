#import matplotlib.pyplot as plt
#import numpy as np
#
#objects = ("5", "7" ,"10", "12", "15")
##          811 , 1135,  1625,  1995,  2493
#
#y_pos = np.arange(len(objects))
#
##       14  , 5  ,  8 , 1, 0
#lista = [50, 17, 28, 3, 0 ]
#
#plt.bar(y_pos, lista, align="center", alpha=0.4)
#plt.xticks(y_pos, objects)
#plt.ylabel("% experiments")
#plt.xlabel("% infected hosts")
#plt.show()
#
lst = [
       842,
       813,
       1952,
       913,
       988,
       1080,
       861,
       1820,
       1403,
       1274,
       954,
       1822,
       1440,
       1271,
       1668,
       939,
       1119,
       897,
       876,
       1719,
       989,
       1995,
       1466,
       906,
       1107,
       2003,
       1834,
       1935,
]

print(sum(lst)/len(lst))
