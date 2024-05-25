#!/bin/bash
####
# 检查未提交的更改
if git diff-index --quiet HEAD --; then
    echo "没有更改需要提交。"
    exit 0
fi

# 添加所有更改到暂存区
git add .

# 提示输入提交信息
echo "请输入提交信息："
read commit_message

# 检查提交信息是否为空
if [ -z "$commit_message" ]; then
    echo "提交信息不能为空。"
    exit 1
fi

# 提交更改
git commit -m "$commit_message"

# 提交成功消息
echo "更改已提交。"

git push

echo "更改已推送到远程仓库。"



