#include <stdio.h>
#include <arpa/inet.h>  // inet_ntop inet_ntoa
#include <netdb.h>


// gethostbyname 和 gethostname 不是一回事儿

int main(int argc,char **argv)
{
    // gethostbyname
    {
        char **pptr;
        char str[INET_ADDRSTRLEN];
        struct hostent *hptr;

        char host[] = "www.qq.com";

        // 开始获取
        hptr = gethostbyname(host);
        if(hptr == NULL)
        {
          printf("gethostbyname error for host: %s: %s\n", host, hstrerror(h_errno));  // 出错信息，并记录在 h_error 中
          return;
        }

        // 正式主机名
        printf("official hostname: %s\n", hptr->h_name);

        // 遍历所有的主机别名
        int alias_count = 0;
        for(pptr=hptr->h_aliases; *pptr!=NULL; pptr++)
        {
            alias_count++;
            printf("\talias: %s\n", *pptr);
        }
        printf("alias_count:%d\n", alias_count);

        // 遍历所有的主机地址
        switch(hptr->h_addrtype) // 判断 socket 类型
        {
          case AF_INET:  // IP 类 为AF_INET
          case AF_INET6:  //IP类为AF_INET6
          {
              int addr_count = 0;
            for(pptr = hptr->h_addr_list; *pptr!=NULL; pptr++)
            {
                addr_count++;
                printf("\taddress: %s\n",
                    inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str))); // inet_ntop 转换为点分十进制

               // printf("\taddress: %s\n",
                    // inet_ntoa(*(struct in_addr*)pptr); // inet_ntoa 转换为点分十进制
            }
              printf("addr_count:%d\n", addr_count);
          }
            break;
          default:
            printf("unknown address type\n");
            break;
        }
    }
    
    // gethostbyaddr
    {
        char **pptr;
        char str[INET_ADDRSTRLEN];
       struct hostent *hptr;
        
       struct sockaddr_in saddr;
        
        char addr[] = "127.0.0.1";
     　　if(!inet_aton(addr, &saddr.sin_addr )) //调用inet_aton()，将ptr点分十进制转in_addr
     　　{
        　　printf("Inet_aton error\n");
         　　return 1;
     　　}
 
        hptr = gethostbyaddr((void *)&saddr.sin_addr, 4, AF_INET);
     　　if(hptr == NULL) //把主机信息保存在hostent中
     　　{
         　　printf("gethostbyaddr error for addr:%s\n", addr);
         　　printf("h_errno %d\n", h_errno);
         　　return 1;
     　　}
    }
    
 
    return 0;
}
