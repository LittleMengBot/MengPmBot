# MengPmBot
管理員指令：  
```/r user_id text```： 向id為user_id的用戶回復text。  
```/ban user_id name```： 封禁user_id的用戶。  
```/unban user_id```： 解封user_id的用戶。  
```/banlist```： 查看黑名單。

# 構建  
1.安裝 https://github.com/reo7sp/tgbot-cpp 並確保  
```Boost >= 1.75```  
```CMake >= 3.17```  
```編譯器支持C++20特性```  

2.運行 ```mkdir build && cmake .. && make```
