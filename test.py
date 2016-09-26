import numpy as np
import _integrate as myint

a = 0.0
b = 1.0
N = 100
x = np.linspace(a, b, N+1)
fi = np.sin(x)

print(myint.riemann(fi, a, b, N))
print(myint.trapezoid(fi, a, b, N))

print("Print")
myint.printGlob()
print("Set")
myint.setGlob()
print("Print")
myint.printGlob()
print("Set")
myint.setGlobExact(285)
print("Print")
myint.printGlob()
