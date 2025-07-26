#!/bin/bash

echo "Testing: echo << k"
echo -e "echo << k\nhello world\nthis is a test\nk\nexit" | ./minishell
echo ""

echo "Testing: cat << EOF"  
echo -e "cat << EOF\nLine 1\nLine 2\nLine 3\nEOF\nexit" | ./minishell
echo ""

echo "Testing: wc -l << END"
echo -e "wc -l << END\nfirst line\nsecond line\nthird line\nEND\nexit" | ./minishell
