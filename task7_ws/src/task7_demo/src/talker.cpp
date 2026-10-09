#include <rclcpp/rclcpp.hpp>
#include <task7_interfaces/msg/custom_message.hpp>
#include <chrono>//C++的时间相关库 
#include <memory>//智能指针

using namespace std::chrono_literals;//这个可以让我们直接写500毫秒

class Talker : public rclcpp::Node//class Talker 定义一个叫Talker的类  :public rclcpp::Node 表示Talker继承ROS2的node 所以Talker就具备了ROS2 NOde 的能力
{
public:
    Talker() : Node("Talker")//调用父类rclcpp::Node的构造函数  并且这个构造函数会自动执行 然后起名叫“Talker”
    {
        publisher_ = this->create_publisher<task7_interfaces::msg::CustomMessage>("/custom_message", 10);//创建/custom_message发布器
        //this 指当前这个Talker对象 可以理解为“我这个Talker”
        //create_publisher 意思是创建一个Publisher（负责发送消息的对象）
        //<task7_interfaces::msg::CustomMessage> 告诉Publisher发的消息类型是CUstomMessage
        //"/custom_message" 表示我要往哪个Topic发布 
        //10 这是一个队列深度参数 大概就是ROS2会保存一定数量的待处理消息 
        //所以说这一行就是  给我创建一个Publisher 它负责把CUstomMessage类型的数据发送到/custom_message这个Topic
        timer_ = this->create_wall_timer(500ms, std::bind(&Talker::timerCallback, this));
        //每500毫秒调用一次timerCallback
        //create_wall_timer  意思是创建一个定时器 500ms意思是每隔500ms触发一次
        //然后 std::bind(&Talker::timerCallback,this)  这个大致意思就是 当定时器到时间的时候 就去调用一次timerCallback()函数
    }

private:
    void timerCallback()//这就是定时器触发之后执行的函数
    {
        task7_interfaces::msg::CustomMessage message;//创建一个CustomMessage类型的变量 名字叫message
        //下面的内容就是和.msg文件里面的有关  就像结构体一样
        message.content = "Hello, ROS 2 Jazzy";//给content字段赋值
        message.counter = count_;//给counter字段赋值
        message.value = 3.14f;//给value字段赋值
        message.header.stamp = this->now();//这个是时间戳 带有产生这条消息的时间

        publisher_->publish(message);//发布消息 把刚刚填好的完整的message发出去

        count_++;//计数器加1
    }

    rclcpp::Publisher<task7_interfaces::msg::CustomMessage>::SharedPtr publisher_;//储存CustomMessage类型的发布器  保存我们刚刚创建的Publisher
    rclcpp::TimerBase::SharedPtr timer_;//储存定时器
    int count_ = 0;//记录已经发布的消息数量
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);//初始化ROS 2

    auto node = std::make_shared<Talker>();//创建Talker节点

    rclcpp::spin(node);//让节点持续运行 并且不断处理ROS2的事件

    rclcpp::shutdown();//关闭ROS 2

    return 0;//程序正常结束
}