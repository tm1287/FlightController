import pygame
import serial
from math import *

ser = serial.Serial("COM3", 115200, timeout=100)


###
### Credit to https://github.com/yuta-51/3DProjection for their projection angorithm
###

WINDOW_SIZE =  800
window = pygame.display.set_mode( (WINDOW_SIZE, WINDOW_SIZE) )
clock = pygame.time.Clock()

projection_matrix = [[1,0,0],
                     [0,1,0],
                     [0,0,0]]

cube_points = [n for n in range(8)]
cube_points[0] = [[-1], [-1], [1]]
cube_points[1] = [[1],[-1],[1]]
cube_points[2] = [[1],[1],[1]]
cube_points[3] = [[-1],[1],[1]]
cube_points[4] = [[-1],[-1],[-1]]
cube_points[5] = [[1],[-1],[-1]]
cube_points[6] = [[1],[1],[-1]]
cube_points[7] = [[-1],[1],[-1]]


def multiply_m(a, b):
    a_rows = len(a)
    a_cols = len(a[0])

    b_rows = len(b)
    b_cols = len(b[0])
    # Dot product matrix dimentions = a_rows x b_cols
    product = [[0 for _ in range(b_cols)] for _ in range(a_rows)]

    if a_cols == b_rows:
        for i in range(a_rows):
            for j in range(b_cols):
                for k in range(b_rows):
                    product[i][j] += a[i][k] * b[k][j]
    else:
        print("INCOMPATIBLE MATRIX SIZES")
    return product        


def connect_points(i, j, points):
    pygame.draw.line(window, (255, 255, 255), (points[i][0], points[i][1]) , (points[j][0], points[j][1]))

# Main Loop
scale = 100
angle_x = 0
angle_y = 0
angle_z = 0
while True:
    [roll, pitch] = ser.readline().decode("utf-8").strip().split(",")
    angle_z = float(roll)/100
    angle_x = float(pitch)/100
    window.fill((0,0,0))
    rotation_x = [[1, 0, 0],
                    [0, cos(angle_x), -sin(angle_x)],
                    [0, sin(angle_x), cos(angle_x)]]

    rotation_y = [[cos(angle_y), 0, sin(angle_y)],
                    [0, 1, 0],
                    [-sin(angle_y), 0, cos(angle_y)]]

    rotation_z = [[cos(angle_z), -sin(angle_z), 0],
                    [sin(angle_z), cos(angle_z), 0],
                    [0, 0, 1]]

    points = [0 for _ in range(len(cube_points))]
    i = 0
    for idx, point in enumerate(cube_points):
        rotate_x = multiply_m(rotation_x, point)
        rotate_y = multiply_m(rotation_y, rotate_x)
        rotate_z = multiply_m(rotation_z, rotate_y)
        point_2d = multiply_m(projection_matrix, rotate_z)
    
        x = (point_2d[0][0] * scale) + WINDOW_SIZE/2
        y = (point_2d[1][0] * scale) + WINDOW_SIZE/2

        points[i] = (x,y)
        i += 1
        if(idx <= 1):
            pygame.draw.circle(window, (255, 0, 0), (x, y), 5)
        elif (idx <= 4):
            pygame.draw.circle(window, (0, 255, 0), (x, y), 5)
        else:
            pygame.draw.circle(window, (0, 0, 255), (x, y), 5)

    connect_points(3, 7, points)
    connect_points(4, 7, points)
    connect_points(6, 7, points)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit() 
          
    pygame.display.update()