RR=`make`
if [ $# -ge 2 ]
then
{
	echo "[ DIFF ] \n"
	diff <(nl <(./ft_ls -G $1 $2 | cat -e)) <(nl <(ls $1 $2 | cat -e))
}
elif [ $# -ge 1 ]
then
{
	./ft_ls -G $1
	ls $1
}
fi
