# T-DT 2027 青训计划 学习任务(6)<br>ROS2 Jazzy基础通信与自定义接口

> + 实验室不愿意淘汰热爱 RM 且勤恳努力的新手，也不会留下不利于团队发展的所谓强者。
> + 每题给出关键词，可根据关键词检索相关知识并完成习题。
> + 完成后将代码和运行结果提交至飞书。

## 学习任务

> **关键词：** ROS 2 Jazzy、rclcpp、Node、Topic、Publisher、Subscriber、自定义消息、rosidl
>
> **任务描述：** 使用 C++ 与 ROS 2 Jazzy，完成一次最基础的发布订阅通信，并在此基础上将标准消息替换为自定义消息。
>
> **目标：** 理解 ROS 2 中“节点通过话题传递消息”的基本工作方式，能够独立创建、编译并运行一个简单 ROS 2 工程。

## 一、环境与工程准备

> 1. 在 Ubuntu 24.04 中安装并验证 ROS 2 Jazzy。
> 2. 创建一个 ROS 2 工作区，并建立使用 `ament_cmake` 的 C++ 功能包。
> 3. 完成编译并运行程序。需要掌握以下基本操作：
>
>    ```bash
>    source /opt/ros/jazzy/setup.bash
>    colcon build --symlink-install
>    source install/setup.bash
>    ```
>
> 4. 知道 `src/`、`build/`、`install/`、`log/` 分别用于什么即可，不要求深入研究其内部结构。

## 二、基础通信：Talker 与 Listener

> 使用 `std_msgs/msg/String` 完成最基本的 ROS 2 发布订阅。
>
> 1. 编写 `talker` 节点，在 `/chatter` 话题上持续发布：
>
>    ```text
>    Hello, ROS 2 Jazzy: N
>    ```
>
>    其中 `N` 随发送次数递增。
> 2. 编写 `listener` 节点，订阅 `/chatter`，并在终端输出收到的消息。
> 3. 使用下面几个命令确认通信确实存在：
>
>    ```bash
>    ros2 node list
>    ros2 topic list
>    ros2 topic echo /chatter
>    ```
>
> 4. 能够说明 `talker`、`listener`、`/chatter` 和 `std_msgs/msg/String` 分别对应 ROS 2 中的什么概念。

## 三、自定义接口：CustomMessage

> 在第二部分能够正常通信后，保留原有 `talker` / `listener` 的整体结构，将消息类型升级为自定义消息。
>
> 1. 新建独立接口包，例如 `task6_interfaces`。
> 2. 创建 `msg/CustomMessage.msg`：
>
>    ```text
>    std_msgs/Header header
>    string content
>    int32 counter
>    float32 value
>    ```
>
> 3. 使用 `rosidl_default_generators` 生成接口，并能够通过下面的命令查看消息定义：
>
>    ```bash
>    ros2 interface show task6_interfaces/msg/CustomMessage
>    ```
>
> 4. 修改 `talker`，在 `/custom_message` 上发布 `CustomMessage`；至少正确填写 `content`、`counter` 和时间戳。
> 5. 修改 `listener`，订阅 `/custom_message` 并输出各字段。
> 6. 使用：
>
>    ```bash
>    ros2 topic echo /custom_message
>    ```
>
>    确认自定义消息能够正常传输。

## 四、思考题

> 完成后在 README 中简要回答：
>
> 1. ROS 2 中 **Node、Topic、Message** 分别是什么？
> 2. Publisher 和 Subscriber 是如何通过 Topic 建立联系的？
> 3. 为什么已有 `std_msgs/msg/String`，工程中还需要自己定义 Message？
> 4. 为什么打开一个新终端后通常需要重新执行 `source`？

## 验收与提交

> **验收要求：**
>
> - `talker` / `listener` 能使用 `std_msgs/msg/String` 正常通信；
> - 能用 `ros2 topic echo` 看到 `/chatter` 的消息；
> - 自定义 `CustomMessage` 能成功生成；
> - `talker` / `listener` 能使用自定义消息正常通信；
> - 能解释 Node、Topic、Message、Publisher、Subscriber 的基本关系。
>
> **提交内容：**
>
> 1. 功能包源码与接口包源码；
> 2. `package.xml`、`CMakeLists.txt`、`msg` 文件和 README；
> 3. 关键运行截图或简短演示视频。
>
> 不提交 `build/`、`install/`、`log/`。
