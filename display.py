# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    display.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#              #
#    Updated: 2022/09/27 15:15:45 by lbenatta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

sns.set_theme()
sns.set_style("darkgrid")

raw_data = pd.read_csv("data.csv")
print(raw_data)
fig, ax = plt.subplots(figsize=(15,15))

a = []
b = []
pas = 100
abscisse = 0
def f(t):
    return (-0.0214*t) + 8499
sns.lineplot(a="abscisse", b ="f(abscisse)", ax=ax)
sns_plot = sns.lineplot(a="abscisse", b ="f(abscisse)", color ='red', linewidth=2.5)
for k in range(0,4000):
     a.append(abscisse)
     b.append(f(abscisse))
     abscisse+=pas
ax.legend(['real price'])
plt.plot(a,b)

sns.lineplot(x="km", y ="price", data = raw_data, style = 'km', markers='X', size=50, color='green', ax=ax)
plt.title('Linear_regression', fontsize = 12, color='red', weight='semibold')
plt.text(200000, 40, "est_price = theta1 x km + theta0", horizontalalignment='center', verticalalignment='center', fontsize = 10, color='blue', weight='semibold')

ax.legend(['estimated price'])
plt.plot()

plt.show()
