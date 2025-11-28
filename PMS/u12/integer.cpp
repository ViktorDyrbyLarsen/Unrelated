#include <iostream>
class Integer {
    private:
        int i;
    public:
        Integer();
        Integer(const Integer& j);
        void set(int newi);
        int get();
        void print();
        int compare(const Integer& j);
        int add(const Integer& j);
        int substract(const Integer& j);
        int multiply(const Integer& j);
        int power(const Integer& j);
};

Integer::Integer(const Integer& j) : i(j.i) {}

Integer::Integer() : i(0) {}

void Integer::set(int newi){
    i = newi;
}

int Integer::get(){
    return i;
}

void Integer::print(){
    std::cout << i << std::endl;
}

int Integer::compare(const Integer& j) {
    if (i < j.i) return -1;
    if (i > j.i) return 1;
    if (i == j.i) return 0;
    return -2;
}

int Integer::add(const Integer& j) {
    return i + j.i;
}
int Integer::substract(const Integer& j) {
    return i - j.i;
}
int Integer::multiply(const Integer& j) {
    return i * j.i;
}
int Integer::power(const Integer& j) {
    for (int k = 1; k < j.i; k++) {
        i = i * i;
    }
    return i;
}


int main(int argc, const char *argv[]) {
    // Exercise 11-3
    Integer result;
    Integer i2, i4, i5, i6, i7;
    i4.set(4);
    i5.set(5);
    i6.set(6);
    i7.set(7);
    
    i.set(42);
    


    // Exercise 11-2
    // Integer j(i);
    // i.set(4);

    // std::cout << "(i,j): (" << i.get() << "," << j.get() << ")" << std::endl;
    // std::cout << i.compare(i) << std::endl;
    // std::cout << i.compare(j) << std::endl;
    // std::cout << j.compare(i) << std::endl;

    
    
    return 0;
}