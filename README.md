# campus_vision · 校园视觉(TDT / RoboMaster 青训)

基于 **ROS2 + OpenCV** 的校园视觉工程:TDT 机器人接口开发(main.cpp / five.cpp)、`tdt_interface` 自定义消息协议、数字识别(SVM)与数据集。

## 目录结构

```
campus_ws/
├── src/campus_vision/              # ROS2 功能包
│   ├── src/main.cpp                # 主程序(多线程视觉 + TDT 接口)
│   ├── src/five.cpp                # 数字识别相关
│   ├── src/per_100_datasets/       # 数字识别数据集(图片)
│   ├── include/campus_vision/      # 头文件
│   └── tdt_interface/              # TDT 自定义消息接口包
├── digit_svm.yml                   # SVM 数字识别模型
├── TDT接口与main.cpp说明.md         # 总说明文档
└── TDT文档/                        # 详细文档
    ├── 0-导读与编写逻辑/
    ├── 1-接口协议/                  # 官方游戏与运行环境、话题协议与 QoS、消息定义
    ├── 2-main.cpp详解/             # 变量清单、逐项核对、函数清单
    ├── 3-运行与排障/               # 编译运行、快速排障、注意事项
    └── 4-官方文档附录/             # 发行说明、接入包说明、许可证
```

## 构建

```bash
cd ~/campus_ws
colcon build --packages-select tdt_interface campus_vision
source install/setup.bash
ros2 run campus_vision campus_vision
```

## 说明

- 平台:ROS2(Humble)+ OpenCV;
- 通信:通过 `tdt_interface` 自定义话题与机器人主控交换数据(详见 `TDT文档/1-接口协议`);
- 本仓库仅包含源码与文档,`build/` `install/` `log/` 等构建产物不入库。
