
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

    def __add__(self, another):
        return vec([self.x + another.x, self.y + another.y, self.z + another.z])

    def __sub__(self, another):
        return vec([self.x - another.x, self.y - another.y, self.z - another.z])

    def __str__(self):
        return '{0} {1} {2}'.format(self.x, self.y, self.z)

""" main """
fin = open('input.txt', 'r')

""" reading part """
pos = vec(readnums(fin))
v = vec(readnums(fin))
m = vec(readnums(fin))
omega = vec(readnums(fin))

""" get board """
b = pos - omega
if b.x > 0:
    print(1)
else:
    print(0)


print(vec.angle(m, vec([0, 0, 1])))
