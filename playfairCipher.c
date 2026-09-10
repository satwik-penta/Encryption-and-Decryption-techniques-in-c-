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

void createMatrix(char key[],char matrix[5][5])
{
    int used[26]={0};
    int k=0;

    for(int i=0;key[i]!='\0';i++)
    {
        char ch=key[i];

        if(ch=='J')
            ch='I';

        if(used[ch-'A']==0)
        {
            matrix[k/5][k%5]=ch;
            used[ch-'A']=1;
            k++;
        }
    }

    for(char ch='A';ch<='Z';ch++)
    {
        if(ch=='J')
            continue;

        if(used[ch-'A']==0)
        {
            matrix[k/5][k%5]=ch;
            used[ch-'A']=1;
            k++;
        }
    }
}

void prepareText(char text[],char prepared[])
{
    int i=0;
    int j=0;

    while(text[i]!='\0')
    {
        char first=text[i];

        if(first=='J')
            first='I';

        if(text[i+1]=='\0')
        {
            prepared[j]=first;
            j++;

            prepared[j]='X';
            j++;

            break;
        }

        char second=text[i+1];

        if(second=='J')
            second='I';

        if(first==second)
        {
            prepared[j]=first;
            j++;

            prepared[j]='X';
            j++;

            i++;
        }
        else
        {
            prepared[j]=first;
            j++;

            prepared[j]=second;
            j++;

            i=i+2;
        }
    }

    prepared[j]='\0';
}

void findPosition(char matrix[5][5],char ch,int *row,int *col)
{
    if(ch=='J')
        ch='I';

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(matrix[i][j]==ch)
            {
                *row=i;
                *col=j;
                return;
            }
        }
    }
}

void encrypt(char text[],char matrix[5][5])
{
    int n=strlen(text);

    for(int i=0;i<n;i=i+2)
    {
        int r1,c1,r2,c2;

        findPosition(matrix,text[i],&r1,&c1);
        findPosition(matrix,text[i+1],&r2,&c2);

        if(r1==r2)
        {
            text[i]=matrix[r1][(c1+1)%5];
            text[i+1]=matrix[r2][(c2+1)%5];
        }
        else if(c1==c2)
        {
            text[i]=matrix[(r1+1)%5][c1];
            text[i+1]=matrix[(r2+1)%5][c2];
        }
        else
        {
            text[i]=matrix[r1][c2];
            text[i+1]=matrix[r2][c1];
        }
    }
}

void decrypt(char text[],char matrix[5][5])
{
    int n=strlen(text);

    for(int i=0;i<n;i=i+2)
    {
        int r1,c1,r2,c2;

        findPosition(matrix,text[i],&r1,&c1);
        findPosition(matrix,text[i+1],&r2,&c2);

        if(r1==r2)
        {
            text[i]=matrix[r1][(c1+4)%5];
            text[i+1]=matrix[r2][(c2+4)%5];
        }
        else if(c1==c2)
        {
            text[i]=matrix[(r1+4)%5][c1];
            text[i+1]=matrix[(r2+4)%5][c2];
        }
        else
        {
            text[i]=matrix[r1][c2];
            text[i+1]=matrix[r2][c1];
        }
    }
}

int main()
{
    char plainText[200];
    char preparedText[200];
    char key[100];
    char matrix[5][5];
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

    printf("Enter the key : ");
    fgets(key,sizeof(key),stdin);

    if(isValid(key)==0)
    {
        printf("Special Characters and digits are not allowed!!");
        return 0;
    }

    toUpperCase(key);
    removeSpaces(key);

    createMatrix(key,matrix);

    printf("Playfair Matrix :\n");

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%c ",matrix[i][j]);
        }

        printf("\n");
    }

    printf("Enter your choice\n1.Encryption\n2.Decryption\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        prepareText(plainText,preparedText);

        printf("Plain text after removing spaces, replacing J with I and handling pairs : %s\n",
               preparedText);

        encrypt(preparedText,matrix);

        printf("Encrypted message : %s",preparedText);
    }
    else if(choice==2)
    {
        toUpperCase(plainText);

        printf("Cipher text after removing spaces and replacing J with I : %s\n",
               plainText);

        decrypt(plainText,matrix);

        printf("Decrypted message : %s",plainText);
    }
    else
    {
        printf("Invalid input");
    }

    return 0;
}