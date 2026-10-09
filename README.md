# campus_ws · 校园视觉

> 🏁 **本项目为「校园赛」开发**(RoboMaster 校园视觉 / TDT 机器人),现作为参赛作品归档于本仓库。

本仓库只包含一个工作区文件夹 **`campus_ws/`**:

| 路径 | 说明 |
|---|---|
| [campus_ws/README.md](campus_ws/README.md) | 项目详情:技术栈、目录结构、构建方式 |
| `campus_ws/src/campus_vision/` | ROS2 功能包(main.cpp / five.cpp / 数字识别数据集 / tdt_interface 消息接口) |
| `campus_ws/digit_svm.yml` | SVM 数字识别模型 |
| `campus_ws/TDT文档/` | 接口协议、main.cpp 详解、运行排障、官方附录 |
| `campus_ws/TDT接口与main.cpp说明.md` | 总说明文档 |

## 快速开始

```bash
cd campus_ws
colcon build --packages-select tdt_interface campus_vision
source install/setup.bash
ros2 run campus_vision campus_vision
```

> 详见 [campus_ws/README.md](campus_ws/README.md)。
