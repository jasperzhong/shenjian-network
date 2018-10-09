if [ $3 ]
then
    echo "多余参数"
    echo -e "\t$0 student.conf initpwd.dat"
    echo
    exit
fi

if [ -z $2 ]
then
    echo "缺少参数"
    echo -e "\t$0 student.conf initpwd.dat"
    echo
    exit
fi


password=$(cat $2)
while read id name extras
do
    if [[ $id =~ \#.* ]] || [ -z $name ] 
    then
        continue
    fi  

    username = useradd u$id

    echo "$password" | passwd --stdin u$id > /dev/null
    
    passwd -e u$id > /dev/null 

    echo "u$id[$name]已建立" 
done < $1