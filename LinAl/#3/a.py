
import math

# approxiamte equality difference value
Eps = 0.001

# read float numbers from file 'f'
def readfloatnums(f):
    line = f.readline()
    array = [float(x) for x in line.split()]
    return array

# read integer numbers from file 'f'
def readintnums(f):
    line = f.readline()
    array = [int(x) for x in line.split()]
    return array

# count absolute value
def abs(x):
    if x < 0:
        return -x
    return x

# 3D-cartesian vector class
class vec:
    # class constructor from coordinates array
    def __init__(self, a):
        self.x = a[0]
        self.y = a[1]
        self.z = a[2]

    # get vector length
    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)

    # normalize (make vector length equal to 1.0)
    def normalize(self):
        len = self.length()
        return vec([self.x / len, self.y / len, self.z / len])

    # count vector reflection from given geometry object
    def reflect(self, geom_object):
        normal = geom_object.n.normalize()
        return self - 2 * (vec.dot(self, normal) / normal.length()) * normal

    # vector dot product (a, b)
    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    # vector cross product [a, b]
    def cross(self, another):
        return vec([self.y * another.z - self.z * another.y, self.z * another.x - self.x * another.z, self.x * another.y - self.y * another.x])

    def __add__(self, other):
        return vec([self.x + other.x, self.y + other.y, self.z + other.z])

    def __mul__(self, const):
        return vec([self.x * const, self.y * const, self.z * const])

    def __rmul__(self, const):
        return vec([self.x * const, self.y * const, self.z * const])

    def __sub__(self, other):
        return vec([self.x - other.x, self.y - other.y, self.z - other.z])

    def __str__(self):
        return str(self.x) + ' ' + str(self.y) + ' ' + str(self.z)

# 3D-cartesian ray (Org point & Dir vector) with energy class
class ray:
    def __init__(self, dir, org, energy):
        self.dir = dir
        self.org = org
        self.energy = energy

    # move to point with given length
    def to_point(self, t):
        return self.org + self.dir * t

    # try to reflect from given object with energy loss
    def reflect(self, geom_object):
        if self.energy == 0:
            return
        self.org = geom_object.intersect(self)
        self.dir = self.dir.reflect(geom_object)
        self.energy -= 1

# 3D-cartesian plane class
class plane:
    # class construct from 3 points (must be complanar)
    def __init__(self, a, b, c):
        ### count Ax + By + Cz + D = 0 koeficients from matrix determinant
        # (x - x0) * ((y1 - y0) * (z2 - z0) - (z1 - z0) * (y2 - y0))
        self.A = a.y * (b.z - c.z) + b.y * (c.z - a.z) + c.y * (a.z - b.z)
        # -(y - y0) * ((x1 - x0) * (z2 - z0) - (z1 - z0) * (x2 - x0))
        self.B = a.z * (b.x - c.x) + b.z * (c.x - a.x) + c.z * (a.x - b.x)
        # (z - z0) * ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0))
        self.C = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)
        # all above without x, y, z
        self.D = -(a.x * (b.y * c.z - c.y * b.z) + b.x * (c.y * a.z - a.y * c.z) + c.x * (a.y * b.z - b.y * a.z))

        # count normal (not normalized)
        self.n = vec([self.A, self.B, self.C])

    # find intersection point with given ray
    def intersect(self, ray):
        q = vec.dot(self.n, ray.dir)
        if abs(q) < Eps:
            return None

        t = -(self.D + vec.dot(self.n, ray.org)) / q
        if t < 0.0:
            return None
        return ray.to_point(t)

# 3D-cartesian box (6 planes) class
class box:
    # class constructor with 4 point (point D is above C)
    def __init__(self, a, b, c, d):
        self.sides = [plane(a, b, c), plane(a, b, d + b - c), plane(a, c + a - b, d + a - b),
                      plane(b, c, d), plane(c, d, a + c - b), plane(d, a + d - c, b + d - c)]

""" main """
fin = open("input.txt", "r")
fout = open("output.txt", "w")

### read data
# get bound box borders
bound_box = box(vec(readfloatnums(fin)), vec(readfloatnums(fin)), vec(readfloatnums(fin)), vec(readfloatnums(fin)))
# get initial ray
ray = ray(vec(readfloatnums(fin)), vec(readfloatnums(fin)), readintnums(fin)[0])
# get mirrors
n = readintnums(fin)[0]
mirrors = []
for i in range(n):
    mirrors.append(plane(vec(readfloatnums(fin)), vec(readfloatnums(fin)), vec(readfloatnums(fin))))
fin.close()

### count reflections
while ray.energy > 0:
    # find closeset bound box intersection point
    box_point = None
    for s in bound_box.sides:
        point = s.intersect(ray)

        # point belongs to plane
        if point is not None and abs((point - ray.org).length()) < Eps:
            continue

        if box_point is None:
            # initial values
            box_point = point
        elif point is not None and (point - ray.org).length() < (box_point - ray.org).length():
            # new closest point
            box_point = point

    # find closest mirror intersection point
    mirror_point = None
    mirror_plane = None
    for m in mirrors:
        point = m.intersect(ray)

        # point belongs to plane
        if point is not None and abs((point - ray.org).length()) < Eps:
            continue

        if mirror_point is None:
            # initial values
            mirror_point = point
            mirror_plane = m
        elif point is not None and (point - ray.org).length() < (mirror_point - ray.org).length():
            # new closeset point
            mirror_point = point
            mirror_plane = m

    # check closest object
    if mirror_point is None or (box_point - ray.org).length() < (mirror_point - ray.org).length():
        # box was closer
        ray.org = box_point
        break

    # reflect ray from mirror
    ray.reflect(mirror_plane)

# output answer
if ray.energy > 0:
    fout.write('1\n')
    fout.write(str(ray.energy) + '\n')
    fout.write(str(ray.org) + '\n')
    fout.write(str(ray.dir) + '\n')
else:
    fout.write('0\n')
    fout.write(str(ray.org) + '\n')
fout.close()
