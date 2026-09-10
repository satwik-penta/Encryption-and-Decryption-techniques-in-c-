#include<stdio.h>
#include<string.h>
void toUpperCase(char key[])
{
    for(int i=0;key[i]!='\0';i++)
    {
        if(key[i]>='a' && key[i]<='z')
        {
            key[i]=(key[i]-'a'+'A');
        }
    }
}
int isValid(char text[])
{
    int n=strlen(text);
    for(int i=0;i<n;i++)
    {
        if(!((text[i] >= 'A' && text[i] <= 'Z') ||
             (text[i] >= 'a' && text[i] <= 'z') ||
             text[i] == ' ' ||
             text[i] == '\n'))
             return 0;
    }
    return 1;  
}
void encrypt(char text[],char key[])
{
    int i=0,j=0;
    int n=strlen(text);
    int keyLen=strlen(key);
    for(i=0;i<n;i++)
    {
        if(text[i]>='A' && text[i]<='Z')
        {
            text[i]=(text[i]-'A'+(key[j%keyLen]-'A'))%26 +'A';
            j++;
        }
        else if(text[i]>='a' && text[i]<='z')
        {
            text[i]=(text[i]-'a'+(key[j%keyLen]-'a'))%26 +'a';
            j++;
        }
    }
}
void decrypt(char text[],char key[])
{
    int i=0,j=0;
    int n=strlen(text);
    int keyLen=strlen(key);
    for(i=0;i<n;i++)
    {
        if(text[i]>='A' && text[i]<='Z')
        {
            text[i]=(text[i]-'A'-(key[j%keyLen]-'A')+26)%26 +'A';
            j++;
        }
        else if(text[i]>='a' && text[i]<='z')
        {
            text[i]=(text[i]-'a'-(key[j%keyLen]-'a')+26)%26 +'a';
            j++;
        }
    }

}
int main(){
    char plainText[100];
    char key[100];
    int choice;
    printf("Enter the plain text : ");
    fgets(plainText,sizeof(plainText),stdin);
    if(isValid(plainText)==0)
    {
        printf("Special Characters and digits are not allowed!!");
        return 0;
    }
    toUpperCase(plainText);
    printf("Enter the key : ");
    scanf("%s",key);
    toUpperCase(key);
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