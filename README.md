# campus_ws · 校园视觉

> 🏁 这是我参加 **T-DT 校园赛(2027)** 培训期间开发的视觉程序;**我因学习原因中途退出了培训**。

## 我做了什么

| 内容 | 说明 |
|---|---|
| `campus_ws/src/campus_vision/` | 我写的 ROS2 节点:`main.cpp`(图像处理 → 目标解算 → 发布瞄准指令)、`five.cpp`(数字识别辅助) |
| `campus_ws/digit_svm.yml` | 数字识别模型(SVM),配 `per_100_datasets` 数据集 |
| `campus_ws/TDT文档/` | 我备赛期间的笔记:接口协议、`main.cpp` 逐项讲解、运行排障(踩过的坑都记在里面) |
| `campus_ws/TDT接口与main.cpp说明.md` | 完整版说明:官方协议 + 我的代码逐行对照 |

## 技术路线

ROS2(Humble)+ OpenCV:接收游戏画面 → 红色灯条检测 → 装甲板配对 → PnP 解算位姿 → 发布 yaw/pitch/开火指令;SVM 识别装甲板数字;通过 `tdt_interface` 自定义话题与游戏主控通信。

## 快速开始

```bash
cd campus_ws
colcon build --packages-select tdt_interface campus_vision
source install/setup.bash
ros2 run campus_vision campus_vision
```
