from sympy import symbols


#Harmonic oscillator proplem
class DifferentiationOperator:
    def __init__(self):
        self.order = 1

    def __call__(self, f):
        for _ in range(self.order):
            

    def __pow__(self, n):
        self.order = n


