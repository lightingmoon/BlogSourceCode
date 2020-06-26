import math
import copy
import numpy as np
import random as rd
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

'''
功能：实现GDPSO算法
'''
# GD-PSO 算法需要的参数（根据论文设置）,在30维下进行实验
W = 0.6  # 惯性权重，根据论文会随着迭代次数改变
C1 = 2.0  # 认知
C2 = 2.0  # 社会
P = []  # 第i个粒子搜索到的历史最优位值
Pifitness = []  # 记录第i个粒子搜索到的历史最优值
Pg = []  # 整个粒子群搜索到的最优位值
Pgfitness = float('inf')  # 记录整个粒子群搜索到的最优值
PgfitnessRecord = []
intervalMin = -600  # 种群搜索区间下限
intervalMax = 600  # 种群搜索区间上限
Vmin = -120  # 粒子的速度下限
Vmax = 120  # 粒子的速度上限
N = 10  # 粒子个数
T = 200000  # 迭代次数
D = 30  # 粒子的维度
particle = []  # 单个粒子，其实质就是30维的向量
swam = []  # 种群
swamFitness = []  # 每一代粒子的适应值
particleVelocity = []  # 每一代粒子在各个维度的速度
bestPositonRecord = []  # 记录每一代粒子群最优位置
bestFitnessRecord = []  # 记录每一代粒子群最优值

# Griewank函数，其在原点处有最小值0
def calcFitness(_particle):
    y1 = 0
    for x in _particle:
        y1 += x * x
    y2 = 1
    for i in range(1, D + 1):
        y2 *= np.cos(_particle[i - 1] / np.sqrt(i))
    return float(y1 - y2 + 1)


# GD-PSO 初始化函数
def init_GDPSO():
    global Pgfitness
    global Pg
    global P
    for _ in range(N):  # 初始化10个粒子
        tParticleVelocity = []
        for _ in range(D):  # 初始化粒子的30个维度
            particle.append(rd.uniform(intervalMin, intervalMax))
            tParticleVelocity.append(rd.uniform(Vmin, Vmax))  # 初始化粒子各个维度的速度
        particleVelocity.append(copy.deepcopy(tParticleVelocity))  # 保存每个粒子的初始速度

        fitness = calcFitness(particle)  # 计算粒子的适应值

        swam.append(copy.deepcopy(particle))  # 对每个粒子进行深拷贝，加入种群
        swamFitness.append(fitness)  # 计算种群所有粒子的适应值

        P = copy.deepcopy(swam)  # 初始化第一代粒子历史最优位值
        Pifitness.append(fitness)  # 初始化第一代粒子历史最优值

        if fitness < Pgfitness:  # 记录第一代最小值和位置
            Pgfitness = fitness
            Pg = copy.deepcopy(particle)
        particle.clear()
        tParticleVelocity.clear()
    PgfitnessRecord.append(np.log10(Pgfitness))
    bestPositonRecord.append(copy.deepcopy(Pg))  # 记录每一代最优位置和最优值
    bestFitnessRecord.append(np.log10(Pgfitness))


''' 更新粒子速度
其速度更新形式和标准粒子群算法相比多了一个高斯扰动项：
    gauss = r * gaussian
    其中 r 表示(0,1)区间服从均匀分布的随机数，gaussian表示服从(0,|Pid|)的高斯分布随机数
    (Pid表示第i个粒子在第t次迭代的最优位置记录)
'''

def updateVelocity(particleVelocity):
    for i, vP in enumerate(particleVelocity):
        for d in range(D):
            vP[d] = W * vP[d] + \
                    C1 * rd.random() * (P[i][d] + rd.random() * rd.gauss(0, math.fabs(P[i][d])) - swam[i][d]) + \
                    C2 * rd.random() * (Pg[d] - swam[i][d])
            if vP[d] < Vmin:
                vP[d] = Vmin
            elif vP[d] > Vmax:
                vP[d] = Vmax


'''更新粒子位置
直接用当前粒子位置加上更新后的速度，再处理越界即可
'''

def updatePositon(swam):
    for i, _particle in enumerate(swam):
        for d in range(D):
            _particle[d] = _particle[d] + particleVelocity[i][d]
            if _particle[d] < intervalMin:
                _particle[d] = intervalMin
            elif _particle[d] > intervalMax:
                _particle[d] = intervalMax


# GD-PSO 初始化
init_GDPSO()

# 主函数进行迭代计算

for _ in range(1, T):
    tParticle = []
    tParticleFitness = float('inf')

    updateVelocity(particleVelocity)  # 更新位置和速度
    updatePositon(swam)

    for i, _particle in enumerate(swam):  # 计算粒子的适应值
        fitness = calcFitness(_particle)
        if tParticleFitness > fitness:
            tParticleFitness = fitness
            tParticle = copy.deepcopy(_particle)
        if fitness < Pifitness[i]:  # 更新粒子历史最优值
            P[i] = copy.deepcopy(_particle)
            Pifitness[i] = fitness
        if fitness < Pgfitness:
            Pg = copy.deepcopy(_particle)
            Pgfitness = fitness

    bestPositonRecord.append(copy.deepcopy(tParticle))  # 记录每一代最优位置和最优值

    if Pgfitness > 0:
        PgfitnessRecord.append(np.log10(Pgfitness))  # 记录每一代历史最优适应值
    else:
       PgfitnessRecord.append(0)
    if tParticleFitness != 0:
        bestFitnessRecord.append(copy.deepcopy(np.log10(tParticleFitness)))
    else:
        bestFitnessRecord.append(0)

print(Pg)
print(Pgfitness)


def moving_average(interval, window_size):
    window = np.ones(int(window_size)) / float(window_size)
    return np.convolve(interval, window, 'same')


# 画出粒子群最优值关于迭代次数的图像
x = [x + 1 for x in range(T)]

X = np.array(x)

FitnessCurve = np.array(PgfitnessRecord)

Y = np.array(bestFitnessRecord)
Y_smooth = moving_average(FitnessCurve, T // 10)

plt.rcParams['font.sans-serif'] = ['SimHei']    #显示中文标签
plt.rcParams['axes.unicode_minus'] = False
plt.xlabel('迭代次数')
plt.ylabel('各代最佳适应值的对数')
plt.grid()

plt.plot(X, FitnessCurve, 'r')
# plt.plot(X, Y, 'b')
# plt.plot(X, Y_smooth, 'r')
plt.legend(['original data', 'smooth data'])

plt.show()
