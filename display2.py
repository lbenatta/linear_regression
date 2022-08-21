import pandas as pd
import numpy as np
#import math
#import argparse
#import sys
#import csv
import seaborn as sns
import matplotlib.pyplot as plt
from termcolor import colored

# raw_data = pd.read_csv("//wsl$/Ubuntu-20.04/home/lolo/WORK/linear_regression/V7/data.csv")
# print(raw_data)

# plt.figure(figsize=(15,7))
# sns.set_style("darkgrid")
# palette = sns.color_palette("mako_r", 6)
# ax = sns.lineplot(x="km", y ="price", data = raw_data, style = 'km', markers=True) 
# plt.title('Linear_regression', fontsize = 10)
# #plt.plot(x,y)

# plt.show()

# a = []
# b = []
# pas = 100
# abscisse = 0
# def f(t):
#     return -0.0214*t + 8499
# for k in range(0,250000):
#     a.append(abscisse)
#     b.append(f(abscisse))
#     abscisse+=pas
# plt.plot(a,b)

# plt.show()
sns.set_theme()
sns.set_style("darkgrid")
sns.color_palette("hls", 8)
sns.set_color_codes(palette='bright')

raw_data = pd.read_csv("//wsl$/Ubuntu-20.04/home/lolo/WORK/linear_regression/V7/data.csv")
print(raw_data)
fig, ax = plt.subplots(figsize=(4,4))

a = []
b = []
pas = 100
abscisse = 0
def f(t):
    return (-0.0214*t) + 8499
sns.lineplot(a="abscisse", b ="f(abscisse)", ax=ax)
#sns.lineplot(a="abscisse", b ="f(abscisse)", color='red', ax=ax)
sns_plot = sns.lineplot(a="abscisse", b ="f(abscisse)", palette=['skyblue'], linewidth=2.5)
for k in range(0,4000):
     a.append(abscisse)
     b.append(f(abscisse))
     abscisse+=pas
#_ = plt.plot(a,b, color="r")
ax.legend(['real price'])
plt.plot(a,b)


sns.lineplot(x="km", y ="price", data = raw_data, style = 'km', markers=True, color='red', ax=ax) 
plt.title('Linear_regression', fontsize = 12, weight='semibold')
plt.text(200000, 45, "price = theta1 x km + theta0", horizontalalignment='center', verticalalignment='center', size='medium', color='blue', weight='semibold')
#plt.text(3+0.2, 4.5, "price = theta1 x km + theta0", horizontalalignment='left', verticalalignment='bottom', size='medium', color='blue', weight='semibold')
#plt.text(3+0.2, 4.5, "price = theta1 x km + theta0", horizontalalignment='right', size='medium', color='red', weight='semibold')

ax.legend(['estimated price'])
plt.plot()


plt.show()

#
