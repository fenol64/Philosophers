
int ft_atoi(char *str)
{
    int res;

    res = 0;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + *str - '0';
        str++;
    }
    return (res);
}