#include<stdio.h>
#include<string.h>

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

void getOrder(char key[],int order[])
{
    int n=strlen(key);

    for(int i=0;i<n;i++)
    {
        order[i]=0;

        for(int j=0;j<n;j++)
        {
            if(key[j]<key[i])
            {
                order[i]++;
            }
            else if(key[j]==key[i] && j<i)
            {
                order[i]++;
            }
        }
    }
}

void encrypt(char text[],char result[],char key[])
{
    int n=strlen(text);
    int cols=strlen(key);
    int rows=(n+cols-1)/cols;

    char matrix[50][50];
    int order[50];
    int k=0;

    getOrder(key,order);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(k<n)
                matrix[i][j]=text[k++];
            else
                matrix[i][j]='X';
        }
    }

    k=0;

    for(int num=0;num<cols;num++)
    {
        for(int j=0;j<cols;j++)
        {
            if(order[j]==num)
            {
                for(int i=0;i<rows;i++)
                {
                    result[k]=matrix[i][j];
                    k++;
                }
            }
        }
    }

    result[k]='\0';
}

void decrypt(char text[],char result[],char key[])
{
    int n=strlen(text);
    int cols=strlen(key);
    int rows=(n+cols-1)/cols;

    char matrix[50][50];
    int order[50];
    int k=0;

    getOrder(key,order);

    for(int num=0;num<cols;num++)
    {
        for(int j=0;j<cols;j++)
        {
            if(order[j]==num)
            {
                for(int i=0;i<rows;i++)
                {
                    matrix[i][j]=text[k++];
                }
            }
        }
    }

    k=0;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            result[k]=matrix[i][j];
            k++;
        }
    }

    result[k]='\0';
}

int main()
{
    char text[500];
    char key1[50];
    char key2[50];

    char result1[500];
    char result2[500];

    int choice;

    printf("Enter the text : ");
    fgets(text,sizeof(text),stdin);

    removeSpaces(text);

    printf("Text after removing spaces : %s\n",text);

    printf("Enter the first key : ");
    fgets(key1,sizeof(key1),stdin);

    removeSpaces(key1);

    printf("Enter the second key : ");
    fgets(key2,sizeof(key2),stdin);

    removeSpaces(key2);

    printf("Enter your choice\n1.Encryption\n2.Decryption\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        encrypt(text,result1,key1);

        encrypt(result1,result2,key2);

        printf("After first transposition : %s\n",result1);
        printf("Encrypted message : %s",result2);
    }
    else if(choice==2)
    {
        decrypt(text,result1,key2);

        decrypt(result1,result2,key1);

        printf("After reversing second transposition : %s\n",result1);
        printf("Decrypted message : %s",result2);
    }
    else
    {
        printf("Invalid input");
    }

    return 0;
}