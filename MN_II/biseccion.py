import numpy as np

def f(x):
    return np.power(x, 3) - x - 1  # Or simply x**3 + x -

def biseccion(a, b, err=1e-6, max_iter=100):
    for i in range(max_iter):
        m = (a + b) / 2
        if abs(f(m)) < err or (b - a) / 2 < err:
            return m

        print("{:.2f}".format(a), "{:.2f}".format(b),  "{:.2f}".format(m), "{:.40f}".format(f(m)))
        if f(a) * f(m) < 0:
            return biseccion(a, m, err, max_iter)  # Return the result of the recursive call
        else:
            return biseccion(m, b, err, max_iter)  # Return the result of the recursive call


# Example usage:
a = 1.0
b = 2.0
print(f"a    b    m    f(m)")
root = biseccion(a, b)
print(f"Approximate root: {root}")
result = f(root)
print(f"f(root): {result}")
