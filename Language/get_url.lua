local js = require("cjson.safe")

Domain = {host = "", count = 0, data = {}}

function Domain:inc_count()
    self.count = self.count + 1
end

function Domain:new(ob)
    ob = ob or {}
    setmetatable(ob, self)
    self.__index = self
    return ob
end


--[[
--功能:获取域名
--参数:
--      cur_url: 当前解析出来的url
--      pattern_domain: 匹配模式
--      http_len: "http://"的长度, 8
--返回: 域名
--]]
local function get_domain_name(cur_url, pattern_domain, http_len)
    domain_name = nil
    domain_beg, domain_end = string.find(cur_url, "/", http_len)
    if (domain_beg ~= nil or domain_end ~= nil) then            -- 有"/"
        domain_beg, domain_end = string.find(cur_url, pattern_domain)
        if (domain_beg ~= nil and domain_end ~= nil) then       -- 匹配域名
            domain_name = string.sub(cur_url, domain_beg, domain_end - 1)
        end
    else
        domain_name = cur_url
    end
    return domain_name
end

--[[
--功能:获取页面(每个域名里面可能有多个页面)
--参数:
--      cur_url: 当前解析出来的url
--      pattern: 匹配模式
--返回: 页面url
--]]
local function get_page(cur_url, pattern)
    url_page = nil
    page_beg, page_end = string.find(cur_url, pattern)
    if (page_beg ~= nil or page_end ~= nil) then
        url_page = string.sub(cur_url, page_beg, page_end - 1)
    end

    --[[
    if (url_page == nil) then
        url_page = cur_url
    end
    ]]
    return url_page
end

--[[
--功能: 查找url,看是否存在
--参数: 
--      table:需要查找的表
--      url: 需要查找的字符串(这个程序里是url,所以写成url)
--]]
local function search_data(table, url)
    for i, val in pairs(table) do
        if (val == url) then
            return true
        end
    end

    return false
end

--[[
--用于table.sort()的cmp函数
--]]
local function cmp(a, b)
    return a.count > b.count
end


--[[
--以下是主程序
--]]

local all_domain = {}
local domain_index = {}               --保存"域名-index",这两个配合使用,用空间换时间

-- 一些用到的匹配模式
local pattern_full = "\"http://.-\""    --去包含""中包含http://的
local pattern_domain = "http://.-/"     --取http://到 /的
local pattern_page = "http://.-?"       --取http://到?的

--开始查找的位置
local search_begin = 0
local http_len = 8
local file_name = "result.json"

--从网上获取数据
local file = io.popen("curl http://www.163.com")
local text = file:read("*all")
local i = 1

--循环,一个一个url解析出来
repeat
    --cur_url = string.match(text, pattern_full, search_begin)
    url_beg, url_end = string.find(text, pattern_full, search_begin)
    cur_url = nil
    if (url_beg ~= nil and url_end ~= nil) then
        cur_url = string.sub(text, url_beg+1, url_end-1)
        search_begin = url_end + 1

        -- 解析域名
        domain_name = get_domain_name(cur_url, pattern_domain, http_len)
        --print(domain_name)

        --解析页面url
        url_page = get_page(cur_url, pattern_page)
        if (url_page == nil and cur_url ~= domain_name and cur_url ~= domain_name.."/") then
            url_page = cur_url
        end

        -- 判断域名是否存在,不存在则加进去,存在查找页面,已经不存在的页面就count+1,存在就不管
        local index = domain_index[domain_name]
        --if (all_domain[domain_name] == nila) then     --不存在
        if (index == nil) then
            --print("all_domain[domain_name] = nil")
            new_ob = Domain:new()
            new_ob.host = domain_name
            new_ob.count = 0
            new_table = {}
            new_ob.data = new_table
            table.insert(new_ob.data, url_page)
            all_domain[i] = new_ob
            domain_index[domain_name] = i
            index = i   --为了后面的
            i = i+1
            --table.insert(all_domain, new_ob)
        elseif (url_page ~= nil) then      -- 并且page不为空,就检查是否存在,不存在就插入
            --local index = domain_index[domain_name]
            if (search_data(all_domain[index].data, url_page) == false) then 
                table.insert(all_domain[index].data, url_page)
            end
        end
        all_domain[index].count = all_domain[index].count + 1
    end

until (cur_url == nil)

--这里排序一下,data和count都要排序
--data
for i, val in pairs(all_domain) do
    table.sort(val.data)
end

-- 根据count排序整个set
table.sort(all_domain, cmp)

--编码为json
local js_domain = js.encode(all_domain)
print(js_domain)

--写到文件
fd = io.open(file_name, "w+")
fd:write(js_domain)
