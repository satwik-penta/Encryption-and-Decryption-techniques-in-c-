#include<stdio.h>
#include<string.h>

void toUpperCase(char text[])
{
    for(int i=0; text[i]!='\0'; i++)
    {
        if(text[i]>='a' && text[i]<='z')
        {
            text[i]=text[i]-'a'+'A';
        }
    }
}

void removeSpaces(char text[])
{
    int i,j=0;

    for(i=0; text[i]!='\0'; i++)
    {
        if(text[i]!=' ' && text[i]!='\n')
        {
            text[j]=text[i];
            j++;
        }
    }

    text[j]='\0';
}

int isValid(char text[])
{
    int n=strlen(text);

    for(int i=0;i<n;i++)
    {
        if(!((text[i]>='A' && text[i]<='Z') ||
             (text[i]>='a' && text[i]<='z') ||
             text[i]==' ' ||
             text[i]=='\n'))
        {
            return 0;
        }
    }

    return 1;
}

void encrypt(char text[],char key[])
{
    int n=strlen(text);

    for(int i=0;i<n;i++)
    {
        text[i]=key[text[i]-'A'];
    }
}

void decrypt(char text[],char key[])
{
    int n=strlen(text);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<26;j++)
        {
            if(key[j]==text[i])
            {
                text[i]=j+'A';
                break;
            }
        }
    }
}

int main()
{
    char text[200];

    char key[]="QWERTYUIOPASDFGHJKLZXCVBNM";

    int choice;

    printf("Enter the plain text : ");
    fgets(text,sizeof(text),stdin);

    if(isValid(text)==0)
    {
        printf("Special Characters and digits are not allowed!!");
        return 0;
    }

    toUpperCase(text);
    removeSpaces(text);

    printf("Text after removing spaces : %s\n",text);

    printf("Substitution key : %s\n",key);

    printf("Enter your choice\n1.Encryption\n2.Decryption\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        encrypt(text,key);

        printf("Encrypted message : %s",text);
    }
    else if(choice==2)
    {
        decrypt(text,key);

        printf("Decrypted message : %s",text);
    }
    else
    {
        printf("Invalid input");
    }

    return 0;
}