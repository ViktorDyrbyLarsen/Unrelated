def MyTrapez(f,a,b,n):
    h = (b-a)/n
    sum_x= (1/2)*(f(a)+f(b))
    for i in range(1,n,1):
        x = a+i*h
        sum_x += f(x)
    sum_x = sum_x*h
    return sum_x