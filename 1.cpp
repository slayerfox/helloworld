#include <stdio.h>
#include <arpa/inet.h>  // inet_ntop inet_ntoa
#include <netdb.h>


// gethostbyname 和 gethostname 不是一回事儿

int main(int argc,char **argv)
{
    char **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;

    char host[] = "www.qq.com";

    // 开始获取
    if((hptr=gethostbyname(host)) == NULL)
    {
      printf("gethostbyname error for host: %s: %s\n", host, hstrerror(h_errno));  // 出错信息，并记录在 h_error 中
      return;
    }
    
    // 正式主机名
    printf("official hostname: %s\n", hptr->h_name);

    // 遍历所有的主机别名
    for(pptr=hptr->h_aliases; *pptr!=NULL; pptr++)
    {
        printf("\talias: %s\n",*pptr);
    }
   
    // 遍历所有的主机地址
    switch(hptr->h_addrtype) // 判断 socket 类型
    {
      case AF_INET:  // IP 类 为AF_INET
      {
          pptr = hptr->h_addr_list; //IP地址数组
        for(; *pptr!=NULL; pptr++)
        {
            printf("\taddress: %s\n",
                inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str))); // inet_ntop 转换为点分十进制

           // printf("\taddress: %s\n",
                // inet_ntoa(*(struct in_addr*)pptr); // inet_ntoa 转换为点分十进制
        }
      }
        break;
      default:
        printf("unknown address type\n");
        break;
    }
 
    return 0;
}
