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

void encrypt(char text[],int key[2][2])
{
    int n=strlen(text);

    for(int i=0;i<n;i=i+2)
    {
        int x1=text[i]-'A';
        int x2=text[i+1]-'A';

        int y1=(key[0][0]*x1 + key[0][1]*x2)%26;
        int y2=(key[1][0]*x1 + key[1][1]*x2)%26;

        text[i]=y1+'A';
        text[i+1]=y2+'A';
    }
}

void decrypt(char text[],int key[2][2])
{
    int det;
    int invDet=0;

    det=(key[0][0]*key[1][1] -
         key[0][1]*key[1][0])%26;

    if(det<0)
        det+=26;

    for(int i=1;i<26;i++)
    {
        if((det*i)%26==1)
        {
            invDet=i;
            break;
        }
    }

    int inverse[2][2];

    inverse[0][0]=(key[1][1]*invDet)%26;
    inverse[0][1]=(-key[0][1]*invDet)%26;
    inverse[1][0]=(-key[1][0]*invDet)%26;
    inverse[1][1]=(key[0][0]*invDet)%26;

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(inverse[i][j]<0)
                inverse[i][j]+=26;
        }
    }

    int n=strlen(text);

    for(int i=0;i<n;i=i+2)
    {
        int x1=text[i]-'A';
        int x2=text[i+1]-'A';

        int y1=(inverse[0][0]*x1 +
                inverse[0][1]*x2)%26;

        int y2=(inverse[1][0]*x1 +
                inverse[1][1]*x2)%26;

        text[i]=y1+'A';
        text[i+1]=y2+'A';
    }
}

int main()
{
    char plainText[100];
    int key[2][2];
    int choice;

    printf("Enter the plain text : ");
    fgets(plainText,sizeof(plainText),stdin);

    if(isValid(plainText)==0)
    {
        printf("Special Characters and digits are not allowed!!");
        return 0;
    }

    toUpperCase(plainText);
    removeSpaces(plainText);

    int n=strlen(plainText);

    if(n%2!=0)
    {
        plainText[n]='X';
        plainText[n+1]='\0';
    }

    printf("Plain text after removing spaces and adding X if required : %s\n",
           plainText);

    printf("Enter the 2x2 key matrix :\n");

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            scanf("%d",&key[i][j]);
        }
    }

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
    {
        printf("Invalid input");
    }

    return 0;
}