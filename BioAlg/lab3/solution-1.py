"""
Calculates RNA folding, returns knot count.

https://en.wikipedia.org/wiki/Nussinov_algorithm
"""

class RNA:
    """ RNA folding class."""
    def __init__(self, str_rna):
        self.s = str_rna
        self.nussinov()

    @staticmethod
    def weight(nuc_1, nuc_2):
        """ Returns 1 if pair complementary and 0 otherwise."""
        complementary = [
            ("A", "U"),
            ("U", "A"),
            ("C", "G"),
            ("G", "C"),
        ]
        return (nuc_1, nuc_2) in complementary

    def nussinov(self):
        """ Builds Nussinov matrix."""
        self.N = [[None] * (len(self.s)) for _ in range(len(self.s))]

        for i in range(len(s)):
            self.N[i][i] = 0
        for i in range(len(s) - 1):
            self.N[i][i + 1] = 0

        for t in range(2, len(s)):
            for i in range(len(s) - t):
                j = i + t
                score_diag = self.N[i + 1][j - 1] + RNA.weight(self.s[i], self.s[j])
                score_join = max(self.N[i][k] + self.N[k + 1][j] for k in range(i, j))
                self.N[i][j] = max(score_diag, score_join)

# solution
s = input()
rna = RNA(s)

print(rna.N[0][-1])
