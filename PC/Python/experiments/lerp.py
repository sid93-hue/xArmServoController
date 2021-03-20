def lerp(i, j, k):
    return int((1 - k) * i + j * k)

def invlerp(i, j, k):
    return (k - i) / (j - i)

def x_round(x):
    return round(x*4) / 4

def angle_to_position(degrees):
    x = x_round(degrees)
    y = invlerp(-125, 125, x)
    return lerp(0, 1000, y)

def position_to_angle(position):
    return lerp(-125, 125, position / 1000)


degrees = 90
print('position', angle_to_position(degrees))

position = 500
print('angle', position_to_angle(position))

# x = 0

# _x = x_round(x)
# print('round', _x)

# _y = invlerp(-125, 125, _x)
# print('invlerp', _y)

# _z = lerp(0, 1000, _y)
# print('lerp', _z)