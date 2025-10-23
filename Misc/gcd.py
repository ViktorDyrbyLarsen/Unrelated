def gcd(a, b):
    """Compute the greatest common divisor of a and b."""
    while b:
        a, b = b, a % b
    return abs(a)

print(gcd(252, 105))  # Example usage, should return 6
