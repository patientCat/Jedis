# Jedis
自己打算一遍学习Redis，一边写一个自己的Jedis出来。

## 1. Reactor
首先完成Reactor的部分
完成了简单日志库

## 2. 简单的Redis
完成了Redis的基本功能
主要是JObject的构建，想到了使用boost::any来进行多态

## 3. Telnet的命令解析
因为只是本地学习，所以采用telnet协议。
完成了了TelnetDecode

## 4. 简单数据结构和命令解析
完成了JString，JList的俩个数据结构的3个基本命令的实现
因为本身不是为了性能考虑，所以直接使用了STL。

做好了命令解析表

## 5. 错误处理
完善了错误处理。交互更加人性化。

## TODO: 6. 持久化和订阅发布

