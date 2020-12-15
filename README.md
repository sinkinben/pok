[![Code Quality Score](https://www.code-inspector.com/project/12/score/svg)](https://www.code-inspector.com/public/project/12/POK/dashboard)
[![Code Grade](https://www.code-inspector.com/project/12/status/svg)](https://www.code-inspector.com/public/project/12/POK/dashboard)
[![Build status](https://travis-ci.org/pok-kernel/pok.svg?master)](https://travis-ci.org/pok-kernel)

POK
===

POK kernel, a secure and safe micro-kernel for embedded systems.

More information on https://pok-kernel.github.io/

For commercial support: http://www.reblochon.io.

Contact: pok at gunnm dot org


## 个人笔记

### 获取时间
如果想要在用户程序（即 `examples` 下面的代码）中使用 `pok_time_get` 获取时间，那么要在 `deployment.h` 中定义：
```c
#define POK_NEEDS_GETTICK 1
```

恕我直（tu）言（cao），这个代码的宏定义设计太反人类的。

### 新增内核调度
原本的 pok-kernel 似乎本来就是支持抢占的，因为在 `boot.c` 中存在这么一句：
```c
pok_arch_preempt_enable();
```
它会调用对应 ARCH 文件夹下的 `arch.c` 的同名函数实现。

几个重要文件：
+ partition.c: `pok_partition_setup_scheduler`, 60 行左右的位置
+ sched.{c,h}: 添加调度算法
+ schedvalues.h: 添加 `switch-case` 的枚举类型

原本的 kernel 只实现了 RMS 和 RR 调度算法 (参考 `partition.c`, 默认是 RR 调度)，要做的就是支持更多的线程调度：
+ POK_SCHED_EDF 
+ POK_SCHED_WRR
+ POK_SCHED_PRIORITY
+ POK_SCHED_MLFQ (选做)

目前改动的代码：
+ 在 `pok_thread_t` 中新增了 2 成员：`weight` 和 `arrive_time`, 以支持 WRR 算法的实现
  - 在 `thread.c` 中均初始化为 0 
  - 在 `examples` 中的用户程序中，目前可以通过 `pok_thread_attr_t` 中的 `weight, arrive_time` 改变线程的权重
+ 在 `pok_partition_t` 中新增成员：`current_weight`:
  - 在 `partition.c` 中初始化为 0 