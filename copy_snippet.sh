#!/bin/bash

SOURCE_DIR="/Users/aaron/Documents/template"
SNIPPET_DIR="/Users/aaron/Library/Application Support/Sublime Text/Packages/User"
TEMP_DIR="/tmp/cpp_template_snippets"

mkdir -p "$TEMP_DIR"

SUBDIRS=("data" "flow" "misc" "string" "graph" "numeric")

# 遍历每个子目录
for subdir in "${SUBDIRS[@]}"; do
	# 查找所有的.cpp文件
	find "$SOURCE_DIR/$subdir" -name "*.cpp" | while read -r file; do
		# 获取文件名（不带扩展名）
		filename=$(basename "$file" .cpp)

		# 创建snippet文件路径
		snippet_file="$TEMP_DIR/$filename.sublime-snippet"

		# 读取文件内容并写入snippet文件
		{
			echo '<snippet>'
			echo '  <content><![CDATA['
			cat "$file"
			echo
			echo ']]></content>'
			echo "  <tabTrigger>$filename</tabTrigger>"
			echo '  <scope>source.c++</scope>'
			echo '</snippet>'
		} >"$snippet_file"

		echo "Created snippet: $snippet_file"
	done
done

# 将生成的snippet文件移动到Sublime Text的snippet目录
mv "$TEMP_DIR"/*.sublime-snippet "$SNIPPET_DIR/" 2>/dev/null

# 清理临时目录
rm -rf "$TEMP_DIR"

echo "All snippets have been created and moved to $SNIPPET_DIR"
