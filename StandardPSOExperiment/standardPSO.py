'''
功能：运用标准粒子群算法解决问题
    求 f(x) = 1-cos(3*x)*exp(-x)在区间[0,4]上的最大值
    用 3个一维粒子组成粒子群，运用速度位置更新公式迭代种群，求解问题
'''
import math
import copy

from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt
import numpy as np
import random as rd

# 标准粒子群算法参数
W = 1   # 惯性权重
C1 = 2.8  # 认知
C2 = 1.3  # 社会
Pi = [] # 第i个粒子搜索到的历史最优位值
Pifitness = []
Pg = 0 # 整个粒子群搜索到的最优位值
Pgfitness = 0
intervalMax = 4
intervalMin = 0
Vmin = -0.001
Vmax = 0.001
swam = [] # 种群
ParFitness = [] # 种群适应值
ParVelocity = [] # 记录粒子i速度
N = 3 # 粒子个数
T = 30 # 迭代次数
record = [] # 粒子群迭代情况
table = [] # 每一代粒子群最优适应值

# 目标函数
def calcFitness(x):
    return float(1 - math.cos(3*x)*math.exp(-x))

# 初始化种群
def initSwam():
    Flag = True
    for i in range(N):
        swam.append(rd.uniform(0,4))     # 初始化种群
        ParVelocity.append(rd.uniform(Vmin, Vmax))  # 初始化粒子速度
        ParFitness.append(calcFitness(swam[i]))  # 初始化种群适应度

        if Flag:        # 初始化种群最优值
            Pg = swam[0]
            Pgfitness = ParFitness[0]
            Flag = False

        Pi.append(swam[i])    # 初始化第i个粒子历史最优位值
        Pifitness.append(ParFitness[i]) # 初始化第i个粒子历史最优值
        if Pifitness[i] > Pgfitness:    # 更新种群最优位置
            Pg = swam[i]
            Pgfitness = Pifitness[i]
# 更新粒子速度
def updateVelocity():
    for i in range(N):
        ParVelocity[i] = W * ParVelocity[i] + C1*(Pi[i] - swam[i]) + C2*(Pg - swam[i])
        # 速度越界处理
        if ParVelocity[i] < Vmin or ParVelocity[i] > Vmax:
            ParVelocity[i] = rd.uniform(Vmin,Vmax)

# 更新粒子位置
def updatePosition():
    for i in range(N):
        swam[i] = swam[i] + ParVelocity[i]
        # 处理粒子越界
        if swam[i] > intervalMax or swam[i] < intervalMax:
            swam[i] = rd.uniform(intervalMin,intervalMax)

# 初始化粒子群
initSwam()

# 进行迭代
for _ in range(T):
    # 记录粒子迭代情况
    record.append(copy.deepcopy(swam))

    # 更新
    updateVelocity()  # 更新粒子速度
    updatePosition()  # 更新粒子位置

    for i in range(N):
        ParFitness[i] = calcFitness(swam[i])    # 计算粒子的适应度
        if ParFitness[i] > Pifitness[i]:        # 记录粒子历史最优适应值
            Pi[i] = swam[i]
            Pifitness[i] = ParFitness[i]
            if Pifitness[i] > Pgfitness:        # 记录种群最优适应值
                Pg = Pi[i]
                Pgfitness = Pifitness[i]
        # print("粒子{0} :{1}, 适应值:{2}".format(i + 1, swam[i], ParFitness[i]), end=" ")
        # print("历史最优值：{0}".format(ParFitness[i]))
    print(Pgfitness)
    table.append(Pgfitness)


print("目标函数最大值为: {0} , 此时 x = {1}".format(Pgfitness, Pg))

plt.title("PSO iteration optimum fitness")
x = [x+1 for x in range(T)]
x_smooth = np.linspace(1,T,100)

y_smooth = make_interp_spline(x,table)(x_smooth)
plt.grid()
plt.plot(x_smooth,y_smooth,'m')
plt.show()

# print("迭代粒子群如下:")
plt.title("PSO iteration")
plt.grid()
xx = np.arange(0,4,0.001)
yy = 1 - np.cos(3*xx)*np.exp(-xx)
plt.plot(xx,yy,"y")

maxY = -float("inf")
maxX = 0
for x in record:
    tx = np.array(x)
    y = 1 - np.cos(3*tx)*np.exp(-tx)
    if maxY < max(y):
        maxY = max(y)
        for xx in x:
            if calcFitness(xx) == maxY:
                maxX = xx
    plt.plot(x,y,"xc")
plt.annotate("Max:{0:.6f}".format(maxY) ,xy = (maxX,maxY),xytext=(maxX + 2, maxY),
             arrowprops=dict(facecolor='black',shrink=0.05),
             horizontalalignment='right',
             verticalalignment='top',
)
plt.show()
