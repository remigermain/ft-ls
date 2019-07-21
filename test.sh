RR=`make`
if [ $# -ge 3 ]
then
{
	echo "[ DIFF ] \n"
	diff <(nl <(./ft_ls -G $1 $2 | cat -e)) <(nl <(ls $1 $2 | cat -e))
}
elif [ $# -ge 2 ]
then
{
	./ft_ls -G $1
	ls $1
}
else
{
	./ft_ls $1
	ls $1
}
fi
