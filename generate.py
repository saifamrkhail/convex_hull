import os

from numpy import sin, cos, pi
import random

cwd = os.getcwd()


def circle_points(n):
    with open(os.path.join(cwd, r'Testfiles', r'Circle', f'{n}.txt'), 'w+') as f:
        for i in range(0,n):
            f.write(f'{round(250 + 150 * cos(2 * pi * i / n), 1)},{round(250 + 150 * sin(2 * pi * i / n), 1)}\n')


def rect_points(n):
    with open(os.path.join(cwd, r'Testfiles', r'Rectangle', f'{n}.txt'), 'w+') as f:
        f.write(f'{round(100.0, 1)},{round(100.0, 1)}\n')
        f.write(f'{round(400.0, 1)},{round(400.0, 1)}\n')
        f.write(f'{round(400.0, 1)},{round(100.0, 1)}\n')
        f.write(f'{round(100.0, 1)},{round(400.0, 1)}\n')
        for i in range(0, n - 4):
            f.write(f'{round(random.uniform(99.9, 399.9), 1)},{round(random.uniform(99.9, 399.9), 1)}\n')


def rand_points(n):
    with open(os.path.join(cwd, r'Testfiles', r'Random', f'{n}.txt'), 'w+') as f:
        for i in range(0, n - 4):
            f.write(f'{round(random.uniform(100.0, 400.0), 1)},{round(random.uniform(100.0, 400.0), 1)}\n')


os.mkdir(os.path.join(cwd, r'Testfiles'))
os.mkdir(os.path.join(cwd, r'Testfiles', r'Circle'))
os.mkdir(os.path.join(cwd, r'Testfiles', r'Rectangle'))
os.mkdir(os.path.join(cwd, r'Testfiles', r'Random'))


for i in range(50000, 300000, 50000):
    rect_points(i)
for i in range(50000, 300000, 50000):
    rand_points(i)
for i in range(50000, 300000, 50000):
    circle_points(i)
