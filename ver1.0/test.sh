
# ./pipex here_doc EOF "cat" "grep -i e" "outfile"
# ( (echo "hello"; echo "EOF") | ./pipex here_doc EOF "grep e" "outfile");
# ( (echo "hello"; echo "EOF") | grep e <<EOF >outfile);
echo \033[31mError