
def readfloatnums(f):
    line = f.readline()
    array = [float(x) for x in line.split()]
    return array

def readintnums(f):
    line = f.readline()
    array = [int(x) for x in line.split()]
    return array

class matrix:
    def read(self, f):
        [self.n, self.m] = readintnums(f)

        self.container = []
        data = readfloatnums(f)
        for i in range(self.n):
            self.container.append([])
            for j in range(self.m):
                self.container[i].append(data[self.m * i + j])

    def write(self, f):
        for i in range(self.n):
            for j in range(self.m - 1):
                f.write(str(self.container[i][j]) + ' ')
            f.write(str(self.container[i][self.m - 1]) + '\n')

    def transpose(self):
        c = matrix()
        c.container = []
        c.n = self.m
        c.m = self.n

        for i in range(c.n):
            c.container.append([])
            for j in range(c.m):
                c.container[i].append(self.container[j][i])
        return c

    def multiply(self, number):
        c = matrix()
        c.container = []
        c.n = self.n
        c.m = self.m

        for i in range(c.n):
            c.container.append([])
            for j in range(c.m):
                c.container[i].append(self.container[i][j] * number)
        return c

    def __add__(self, another):
        if self.n != another.n or self.m != another.m:
            raise ValueError

        c = matrix()
        c.container = []
        c.n = self.n
        c.m = self.m

        for i in range(c.n):
            c.container.append([])
            for j in range(c.m):
                c.container[i].append(self.container[i][j] + another.container[i][j])
        return c

    def __sub__(self, another):
        if self.n != another.n or self.m != another.m:
            raise ValueError

        c = matrix()
        c.container = []
        c.n = self.n
        c.m = self.m

        for i in range(c.n):
            c.container.append([])
            for j in range(c.m):
                c.container[i].append(self.container[i][j] - another.container[i][j])
        return c

    def __mul__(self, another):
        if self.m != another.n:
            raise ValueError

        c = matrix()
        c.container = []
        c.n = self.n
        c.m = another.m

        for i in range(c.n):
            c.container.append([])
            for j in range(c.m):
                sum = 0
                for k in range(self.m):
                    sum += self.container[i][k] * another.container[k][j]
                c.container[i].append(sum)
        return c

""" main """
# reading part
fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

[alpha, beta] = readfloatnums(fin)

matrices = []
for i in range(5):
    m = matrix()
    m.read(fin)
    matrices.append(m)

# calculate equatation
try:
    x = (matrices[2] * (matrices[0].multiply(alpha) + matrices[1].multiply(beta).transpose()).transpose()) * matrices[3] - matrices[4]
    fout.write(str(1) + '\n')
    fout.write('{0} {1}\n'.format(x.n, x.m))
    x.write(fout)
except ValueError:
    fout.write(str(0) + '\n')
fin.close()
fout.close()
