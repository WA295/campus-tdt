# T-DT 2027 青训计划 学习任务(7)<br>ROS2 Jazzy图像通信与组件化

> + 实验室不愿意淘汰热爱 RM 且勤恳努力的新手，也不会留下不利于团队发展的所谓强者。
> + 每题给出关键词，可根据关键词检索相关知识并完成习题。
> + 完成后将代码和运行结果提交至飞书。

## 学习任务

> **关键词：** ROS 2 Component、rclcpp_components、sensor_msgs/Image、cv_bridge、OpenCV、RViz2、进程内通信
>
> **任务描述：** 在上一学习任务掌握 ROS 2 基础通信的基础上，将通信内容从简单字符串升级为图像，并进一步了解 ROS 2 Component 的基本使用方式。
>
> **目标：** 能够完成 OpenCV 图像与 ROS 2 Image 消息之间的转换、发布、订阅和可视化；理解普通节点与可组合组件的区别，并能将两个组件装载到同一个容器中运行。

## 一、图像发布与订阅

> 1. 编写图像发布节点，使用 OpenCV 创建一幅图像，并在图像中央绘制：
>
>    ```text
>    Hello, ROS 2 Jazzy: N
>    ```
>
>    其中 `N` 随发送次数递增。
> 2. 将图像转换为 `sensor_msgs/msg/Image`，发布到 `/camera/image`。建议默认使用 **1920 × 1080、10 Hz**，不要求使用原题中的超高分辨率进行压力测试。
> 3. 正确填写消息的 `header.stamp`、`frame_id` 和图像编码。
> 4. 编写订阅节点，订阅 `/camera/image`，使用 `cv_bridge` 转换回 `cv::Mat` 并通过 OpenCV 窗口显示。
> 5. 使用以下命令确认图像话题存在并持续发布：
>
>    ```bash
>    ros2 topic list
>    ros2 topic info /camera/image
>    ros2 topic hz /camera/image
>    ```

## 二、使用 RViz2 查看图像

> 1. 启动 RViz2，在 Displays 中添加 **Image**。
> 2. 将 Topic 设置为 `/camera/image`，确认能够看到与 OpenCV 窗口一致的画面。
> 3. 若没有图像，至少能够使用 `ros2 topic list`、`ros2 topic info` 和 `ros2 topic hz` 判断：
>    - 话题是否存在；
>    - 是否有发布者；
>    - 是否真的持续有消息发出。
>
> 本任务不要求深入分析 TF、复杂 QoS 或 RViz2 的高级配置，重点是把图像通信链路跑通。

## 三、ROS 2 Component

> 在前两部分能够正常运行后，将发布端和订阅端改写为可组合组件。
>
> 1. 创建 `ImagePublisherComponent` 与 `ImageSubscriberComponent`，使用 `rclcpp_components` 注册。
> 2. 能够通过以下命令查看已经注册的组件类型：
>
>    ```bash
>    ros2 component types
>    ```
>
> 3. 编写 `task7.launch.py`，将两个组件加载到同一个 `component_container_mt` 中运行。
> 4. 为容器开启：
>
>    ```text
>    use_intra_process_comms = true
>    ```
>
>    能够说明“两个普通节点分别运行”与“两个组件装入同一个容器”在程序组织形式上的区别即可。

## 四、简单对比与思考

> 完成后在 README 中简要回答：
>
> 1. `cv::Mat` 为什么不能直接作为 ROS 2 Topic 的消息类型发送？`cv_bridge` 在这里起什么作用？
> 2. `sensor_msgs/msg/Image` 中的 `encoding`、`width`、`height` 分别表示什么？
> 3. ROS 2 Component 和普通可执行节点的主要区别是什么？
> 4. 为什么图像这种数据量较大的消息适合了解进程内通信？
>
> **选做：** 将图像尺寸提高到原题的 **4000 × 3096、10 Hz**，分别关闭和开启 `use_intra_process_comms`，使用 `ros2 topic hz` 观察是否有明显差异。只需要记录现象并给出自己的理解，不要求进行 CPU、RSS、带宽等完整性能测试。

## 验收与提交

> **验收要求：**
>
> - `/camera/image` 能持续发布图像；
> - 订阅端能够通过 `cv_bridge` 正确显示；
> - RViz2 能够显示同一图像话题；
> - 两个节点能够改写为 Component，并由同一个容器启动；
> - 能解释 Image 消息、cv_bridge 和 Component 的基本作用。
>
> **提交内容：**
>
> 1. 功能包源码；
> 2. `package.xml`、`CMakeLists.txt`、`task7.launch.py` 和 README；
> 3. OpenCV 窗口、RViz2 显示结果和组件运行结果的截图或简短演示视频。
>
> 不要求提交 GDB 调试记录、故障演练或完整性能测试报告。
