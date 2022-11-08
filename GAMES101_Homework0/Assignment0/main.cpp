#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>


int transformation(){
    std::cout << "Part2: Transformation practice \n";
    float the = 45.0/180.0*acos(-1);
    Eigen::Vector2f p{2.0,1.0}, mov{1.0,2.0};
    Eigen::Matrix2f rot;
    rot << cos(the), -sin(the), 
        sin(the), cos(the);
    std::cout << "p = \n" << p << std::endl;
    std::cout << "rot = \n" << rot << std::endl;
    p = rot*p;
    std::cout << "rotate 45*, p = \n" << p << std::endl;
    p = p+mov;
    std::cout << "then move (1,2), p = \n" << p << std::endl;


    return 0;
}

int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,5.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;
    // MY multiplication Practice
    std::cout << "Practice of vector dot multiplication \n";
    std::cout << "vT * w \n";
    std::cout << v.transpose() * w << std::endl;
    std::cout << v.dot(w) << std::endl;
    std::cout << "wT * v \n";
    std::cout << w.transpose() * v << std::endl;
    std::cout << w.dot(v) << std::endl;
    std::cout << "Practice of vector cross multiplication \n";
    std::cout << w.cross(v) << std::endl;
    std::cout << v.cross(w) << std::endl;
    // MY other multiplication Practice
    std::cout << "Practice of vector other multiplication \n";
    std::cout << "w * Tv \n";
    std::cout << w * v.transpose() << std::endl;
    std::cout << "v * wT \n";
    std::cout << w * v.transpose() << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << "i = \n" << i << std::endl;
    std::cout << "j = \n" << j << std::endl;
    // matrix add i + j
    std::cout << "Practice of i + j \n" << "i+j = \n";
    std::cout << i + j << std::endl;
    // matrix scalar multiply i * 2.0
    std::cout << "Practice of i * 2 \n" << "i*2 = \n";
    std::cout << i*2 << std::endl;
    std::cout << "Practice of i * 2.0 \n" << "i*2.0 = \n";
    std::cout << i*2.0f << std::endl;
    std::cout << "Practice of i * 2.1 \n" << "i*2.1 = \n";
    std::cout << i*2.1f << std::endl;
    // matrix multiply i * j
    std::cout << "Practice of i * j \n" << "i*j = \n";
    std::cout << i*j << std::endl;
    // matrix multiply vector i * v
    std::cout << "Practice of i * v \n" << "i*v = \n";
    std::cout << i*v << std::endl;

    transformation();

    return 0;


}
