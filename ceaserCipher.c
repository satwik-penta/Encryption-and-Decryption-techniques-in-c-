#include <stdio.h>
#include <string.h>
int isValid(char text[])
{
    int n=strlen(text);
    for(int i=0;i<n;i++)
    {
        if(!((text[i] >= 'A' && text[i] <= 'Z') ||
             (text[i] >= 'a' && text[i] <= 'z') ||
             (text[i] >= '0' && text[i] <= '9') ||
             text[i] == ' ' ||
             text[i] == '\n'))
             return 0;
    }
    return 1;  
}
void encrypt(char text[],int key)
{
    int i;
    key=key%26;
    int n=strlen(text);
    for(i=0;i<n;i++)
    {
        if(text[i]>='A' && text[i]<='Z')
        {
            text[i]=(text[i]-'A'+key)%26 + 'A';
        }
        else if(text[i]>='a' && text[i]<='z')
        {
            text[i]=(text[i]-'a'+key)%26 + 'a';
        }
        else if(text[i]>='0' && text[i]<='9')
        {
            int digitKey=key%10;
            text[i]=(text[i]-'0'+digitKey)%10 + '0';
        }
        else if(text[i]==' '){
            continue;
        }
    }
}
void decrypt(char text[],int key)
{
    int i;
    key=key%26;
    int n=strlen(text);
    for(i=0;i<n;i++)
    {
        if(text[i]>='A' && text[i]<='Z')
        {
            text[i]=(text[i]-'A'-key+26)%26 + 'A';
        }
        else if(text[i]>='a' && text[i]<='z')
        {
            text[i]=(text[i]-'a'-key+26)%26 + 'a';
        }
        else if(text[i]>='0' && text[i]<='9')
        {
            int digitKey=key%10;
            text[i]=(text[i]-'0'-digitKey+10)%10 + '0';
        }
        else{
        }
    }
}
int main(){
    char plainText[100];
    int key,choice;
    printf("Enter the plain text : ");
    fgets(plainText,sizeof(plainText),stdin);
    if(isValid(plainText)==0)
    {
        printf("Special Characters are not allowed!!");
        return 0;
    }
    printf("Enter the key : ");
    scanf("%d",&key);
    printf("Enter your choice\n1.Encryption\n2.Decryption\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        encrypt(plainText,key);
        printf("Encrypted message : %s",plainText);
    }
    else if(choice==2)
    {
        decrypt(plainText,key);
        printf("Decrypted message : %s",plainText);
    }
    else
    printf("Invalid input");
return 0;
}