
import math

def readnums(f):
    line = f.readline()
    array = [float(x) for x in line.split()]
    return array

class vec:
    def __init__(self, a):
        self.x = a[0]
        self.y = a[1]
        self.z = a[2]

    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    def normalize(self):
        len = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
        self.x /= len
        self.y /= len
        self.z /= len
        return self

    def normalizing(self):
        len = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
        return vec([self.x / len, self.y / len, self.z / len])

    def cross(self, another):
        return vec([self.y * another.z - self.z * another.y, self.z * another.x - self.x * another.z, self.x * another.y - self.y * another.x])

    def dot(self, another):
        return self.x * another.x + self.y * another.y + self.z * another.z

    def angle(self, another):
        cosine = vec.dot(self, another) / (self.length() * another.length())
        return math.acos(cosine) * (180.0 / math.pi)

    def inverse(self):
        return vec([-self.x, -self.y, -self.z])

    def __add__(self, another):
        return vec([self.x + another.x, self.y + another.y, self.z + another.z])

    def __sub__(self, another):
        return vec([self.x - another.x, self.y - another.y, self.z - another.z])

    def __str__(self):
        return '{0} {1} {2}'.format(self.x, self.y, self.z)

""" main """
fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

### reading part
v = vec(readnums(fin))
a = vec(readnums(fin))
m = vec(readnums(fin))
omega = vec(readnums(fin))

### get board angle
fire_direction = omega - v
board_direction = vec.cross(vec([0, 0, 1]), a)
cannon_angle = vec.angle(fire_direction, board_direction)
state = 1
if cannon_angle > 90.0:
    # change board to opposite
    state = -1
    cannon_angle = vec.angle(fire_direction, board_direction.inverse())

# check firing possibility
if cannon_angle > 60.0:
    state = 0

# set cannon angle sign
if vec.angle(a, fire_direction) > 90.0:
    cannon_angle *= -1

### get mast angle
mast_angle = 90.0 - vec.angle(m, board_direction)
if abs(mast_angle) > 60.0:
    state = 0

### output result
fout.write(str(state) + '\n')

# terminating if we can't fire
if state == 0:
    print("goodbye\n")
    exit(0)

fout.write(str(cannon_angle) + '\n')
fout.write(str(mast_angle) + '\n')
fout.write("super_class\n")

fin.close()
fout.close()
