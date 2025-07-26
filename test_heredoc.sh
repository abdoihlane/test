#!/bin/bash

# Test heredoc functionality
echo "Testing heredoc with 'echo << l'"
echo -e "echo << l\nhello\nworld\nl\nexit" | ./minishell

echo -e "\n\nTesting heredoc with 'cat << EOF'"
echo -e "cat << EOF\nThis is a test\nAnother line\nEOF\nexit" | ./minishell
