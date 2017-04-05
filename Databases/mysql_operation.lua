luasql = require "luasql.mysql"

--创建环境对象
env = luasql.mysql()

--连接数据库
--connet("数据库名“, "用户名", "密码", "IP地址", 端口)
conn = env:connect("isshe", "root", "root", "localhost", 3306)

--设置数据库的编码格式
--conn:execute"SET NAMES UTF8"


--执行数据库操作
cur = conn:execute("select * from chudai")

row = cur:fetch({}, "a")

--文件对象的创建
file = io.open("chudai.db", "w+");  --这里为什么又要分号

while row do 
    val = string.format("id = %d, name = %s\n", row.id, row.username)
    print(val)
    file:write(val)
    row = cur:fetch(row, "a")
end

file:close()
conn:close()
env:close()
