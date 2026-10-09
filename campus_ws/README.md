# campus_vision · 我的校园赛视觉程序

这是我参加 **T-DT 校园赛**时写的 ROS2 视觉节点,干的活:

**收到游戏画面 → 找红色灯条 → 两两配对成装甲板 → PnP 算目标位姿 → 把 yaw/pitch/开火许可发给游戏 → SVM 认数字。**

## 目录

```
campus_ws/
├── src/campus_vision/
│   ├── src/main.cpp              # 主程序,核心逻辑 11 步(详解见 TDT文档)
│   ├── src/five.cpp              # 数字识别相关
│   ├── src/per_100_datasets/     # 数字识别数据集
│   ├── include/campus_vision/    # 头文件
│   └── tdt_interface/            # 和游戏约定的消息接口
├── digit_svm.yml                 # SVM 数字识别模型
├── TDT接口与main.cpp说明.md       # 完整版说明(协议 + 代码逐行对照)
└── TDT文档/                      # 我的备赛笔记(分章版,按需查阅)
```

## 怎么跑

```bash
cd ~/campus_ws
colcon build --packages-select tdt_interface campus_vision
source install/setup.bash
ros2 run campus_vision campus_vision
```

## 我踩过的坑

都整理在 `TDT文档/3-运行与排障/` 里了,比如:

- 每 3 帧才处理 1 帧,不然 CPU 扛不住;
- 话题要用 best_effort QoS,不然收不到游戏画面;
- 数字识别先用 SVM 兜底,识别率不足再上更强的模型。

> 想看整体逻辑 → `TDT文档/0-导读与编写逻辑/00-导读与编写逻辑.md`;
> 想查某个函数/变量 → `TDT文档/2-main.cpp详解/` 里的清单;
> 出毛病了 → `TDT文档/3-运行与排障/10-快速排障.md`。
