#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shape {
public:
  virtual ~Shape() = default;

  virtual double area() const = 0;

  // 功能练习：取消下面注释，并在派生类中实现。
  // virtual double perimeter() const = 0;
  // virtual string type() const = 0;
  // virtual void scale(double factor) = 0;
};

class Circle : public Shape {
  // TODO:
  // 1. 使用 private 成员变量保存半径
  // 2. 编写构造函数
  // 3. override area()
  // 4. 功能练习：perimeter() / type() / scale()
};

class Rectangle : public Shape {
  // TODO:
  // 1. 保存长和宽
  // 2. 编写构造函数
  // 3. override area()
  // 4. 功能练习：perimeter() / type() / scale()
};

class Triangle : public Shape {
  // TODO:
  // 1. 保存三条边
  // 2. 编写构造函数
  // 3. 使用海伦公式实现 area()
  // 4. 功能练习：perimeter() / type() / scale()
};

// 功能练习：可以把统计逻辑拆成函数，参数只依赖 Shape 的公共接口。
// double totalArea(const vector<Shape*>& shapes) { ... }
// const Shape* maxAreaShape(const vector<Shape*>& shapes) { ... }
// void printAll(const vector<Shape*>& shapes) { ... }

int main() {
  int n;
  cin >> n;

  vector<Shape*> shapes;
  shapes.reserve(n);

  for (int i = 0; i < n; ++i) {
    string type;
    cin >> type;

    // TODO: 根据输入创建 Circle / Rectangle / Triangle 对象，
    //       并统一以 Shape* 的形式放入 shapes。
  }

  cout << fixed << setprecision(2);

  // 基础任务：只通过 Shape* 调用 area()，输出每个图形面积。
  for (const Shape* shape : shapes) {
    cout << shape->area() << '\n';
  }

  // TODO: 功能练习
  // 1. 输出 type / area / perimeter
  // 2. 计算总面积
  // 3. 找出面积最大的图形
  // 4. 测试 scale(factor) 后再次输出结果
  // 5. 可选：按 area() 排序

  // 如果仍使用裸指针，请正确释放对象。
  for (Shape* shape : shapes) {
    delete shape;
  }

  return 0;
}
