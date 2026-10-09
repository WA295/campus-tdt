任务中的几个问题
1. NOde是ROS2中一个运行的功能单元  可以负责发布消息 订阅消息或者执行其他任务  
Topic是NOde之间进行消息通信的通道  本次代码文件里面 使用/custom_message作为通信Topic Talker将消息发布到该Topic
Listener订阅该Topic
Message是Topic上实际传输的数据结构  本次使用的自定义的task6_interfaces/msg/CustomMessage，其中包含header content counter value 这四个

2.
在Talker中我们写 
publisher_=this->create_publisher<task6_interfaces::msg::CustomMessage>("/custom_message",10);
这句就是创建一个Publisher  并让它向/customer_message发布CUstomMessage
真正发送的时候 先定义一个变量message  然后写 
publisher_->publish(message);   就将消息发布了出去

在Listener中
写  subscription_=this->create_subscription<task6_interfaces::mag::CustomMessage>("/custmo_message",10,std......)

通过这样 Publisher和Subscriber就可以通过Topic 来进行联系了

3.对于已有的std_msgs/msg/String  工程中还需要自己定义Message 
是因为std_msgs/msg/String 只适合简单的字符串通信
而自定义的Message可以自己定义各种变量
对于工程的进行会更加方便

4.打开终端后需要重新执行source    
是因为一个终端的source 不会在另一个终端里面生效 所以需要重新执行一次




附：
今日学习总结
ROS2 jazzy基础通信与自定义接口

一个ros2程序->可以运行成Node->Node可以通过Topic通信->Topic上传递Message->Publisher 负责发送 Subscriber负责接收->标准 Message发现不够用 -> 自己定义CUstomMessage -> 生成接口-> C++节点使用


今天使用的工作空间
/home/robot/task6_ws
打开终端 进入工作空间 cd task6_ws
工作空间的主要结构
task6_ws/
├── src/
│   ├── task6_demo/
│   │   ├── src/
│   │   │   ├── talker.cpp
│   │   │   └── listener.cpp
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   │
│   └── task6_interfaces/
│       ├── msg/
│       │   └── CustomMessage.msg
│       ├── CMakeLists.txt
│       └── package.xml
│
├── build/
├── install/
└── log/

对于目录的理解 
src 存放编写的ROS2源代码和功能包
build 存放编译过程中产生的文件
install 存放编译安装后的ROS2 package和相关内容
log 存放编译过程中的日志


今天最常使用  source /opt/ros/jazzy/setup.bash  将ROS2 jazzy的环境配置加载到当前终端
只有加载后 当前终端才能正常使用ROS2 jazzy的命令和相关package
之后还经常执行 source ~/task6_ws/install/setup.bash
这个命令就是加载自己的这个工作空间编译安装后的package 让当前终端能够找到task6_demo和task6_interfaces
新开终端后需要重新执行source 因为之前终端中加载的环境不会自动继承到新的终端里面


Talker 
首先使用ROS2自带的 std_msgs/msg./string 编写Talker节点（Node）
主要作用就是创建Publisher 并不断向/chatter发布字符串消息
Listener
同样是一个Node 创建了Subscriber 订阅/chatter 消息类型 std_msgs/msg/String
然后在回调函数中输出收到的数据



使用ROS2命令验证基础通信
ros2 node topic  查看当前正在运行的ros2节点
ros2 topic list  查看当前ROS2系统中存在的Topic
ros2 topic echo /chatter 直接查看/chatter上实际传输的Message



基础通信完成后 开始把标准的std_msgs/msg/String
升级成task6_interfaces/msg/CustomMessage
同时把Topic从/chatter改成了/custom_message


创建独立接口包task6_interfaces
这个包的任务不是编写Talker和listener  而是专门定义ROS2Message

创建CustMessage.msg
最终内容：
std_msgs/Header header
string content
int32 counter
float32 value

今天遇到的第一个问题 CUstomMessage文件为空
最开始检查 cat ~/task6_ws/src/task6_interfaces/msg/CutsomMessage.msg（作用是直接查看文件里面的内容）
但是终端没有任何输出 说明这个路径对应的.msg文件实际上是空的  
因此重新指明真正的文件
code ~/task6_ws/src/task6_interfaces/msg/CustomMessage.msg
然后再次写入 
std_msgs/msg/Header header
string content
int32 counter
float32 value
保存之后再次检查cat ~/task6_ws/src/task6_interfaces/msg/CutsomMessage.msg  这次能够正确看到四行内容
说明编辑器里面看到的文件 不一定就是程序实际使用的文件

修改.msg文件之后 删除之前的构建结果 rm -rf build install log
避免旧的的构建结果影响新的接口生成
然后重新加载ROS2 source /opt/ros/jazzy/setup.bash
然后重新编译 colcon build --symlink-install
编译完成后再输入命令 source install/setup.bash 加载最新编译出来的接口和package


检查自定义接口是否生成成功时使用 ros2 interface show task6_interfaces/msg/CustomMessage  查看ROS2当前生成的CUstomMessage接口结构
最终正确显示 
std_msgs/Header header
string content
int32 counter
float32 value


修改Talker
原来的Talker使用：std_msgs/msg/String
现在修改为 ： task6_interfaces/msg/CustomMessage
原来的Topic：/chatter
修改为：/custom_message


在Talker中创建
    task6_interfaces::msg::CustomMessage message;
然后分别设置
message.content= "Hello,ROS 2 jazzy";
message.counter=count_；设置当前消息的计数值
message.value=3.14f;给浮点字段设置测试值
message.header.stamp=this->now(); 使用当前ROS2时间填写消息的时间戳
最后
publisher_->publish(message);将完整的CUstomMessage发布到/custom_message


修改CMakeLists.txt
因为Talker开始使用task6_interfaces
所以CMakeLists.txt中需要声明
find_package(task6_interfaces REQUIRED)
并且Talker的依赖中加入：task6_interfaces  listener后来也要加入相同的依赖
也就是说 程序代码使用了哪个ROS2 package  CMakeLists.txt就需要正确声明对应的依赖