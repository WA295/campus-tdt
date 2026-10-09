#include <rclcpp/rclcpp.hpp>//引入的是ROS2 C++库
#include <task6_interfaces/msg/custom_message.hpp>//使用我们自己定义的CUstomMessage 我们在.msg文件里面写的四行代码 ROS2根据这个.msg文件生成了对应的C++类型
#include <memory>
#include <functional>

class Listener : public rclcpp::Node
{
public:
    Listener()
        : Node("listener")//创建名字为listener的节点
    {
        subscription_=
            this->create_subscription<task6_interfaces::msg::CustomMessage>(
                "/custom_messag",
                10,
                std::bind(
                    &Listener::messageCallback,
                    this,
                    std::placeholders::_1
                )
            );//创建/chatter订阅器
    }

private:
    rclcpp::Subscription<
        task6_interfaces::msg::CustomMessage
    >::SharedPtr subscription_;//储存订阅器

    void messageCallback(
        const task6_interfaces::msg::CustomMessage::SharedPtr message
    )
    {
        RCLCPP_INFO(
    this->get_logger(),
    "content: %s, counter: %d, value: %.2f",
    message->content.c_str(),
    message->counter,
    message->value
    );
    }
};
int main(int argc,char* argv[])
{
    rclcpp::init(argc,argv);//初始化ROS 2

    auto node=
        std::make_shared<Listener>();//创建Listener节点

    rclcpp::spin(node);//让节点持续运行

    rclcpp::shutdown();//关闭ROS 2

    return 0;
} 
