#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *user, *pass ;
char usersarray[50][50];
char passArray[50][50];
int logidx;

int compare_string(char *first, char *second)
{
    while (*first == *second)
    {
        if (*first == '\0' || *second == '\0' || *first=='\n' || *second== '\n')
            break;

        first++;
        second++;
    }

    if ( *first == '\0' && (*second == '\0'  || *second == '\n')  )
        return 0;
    else
        return -1;
}
void CreateAccount()
{
    if ((user = fopen("Username.txt", "a") ) == NULL || (pass = fopen ("Pass.txt", "a")) == NULL )
    {
        printf("an error happened while opening files");
        return 0;
    }
    // take new account data
    printf("Enter a username and a password");
    char username[50];
    char password[50];
    scanf("%s", username);
    scanf("%s", password);
    printf("New account added.\nUsername: %s \nPassword: %s\n", username, password);
    // Append data to the files
    fputs( username, user);
    fwrite("\n", sizeof(char), 1, user);
    fputs(password, pass);
    fwrite("\n", sizeof(char), 1, pass);
    fclose(user);
    fclose(pass);

}
void GetFileData()
{
    //open file to read
    if ((user = fopen("Username.txt", "r") ) == NULL || (pass = fopen ("Pass.txt", "r")) == NULL )
    {
        printf("an error happened while opening files");
        return 0;
    }
    char name[50];
    int i=0, k=0;
    // store users data in an array
    while(!feof(user))
    {
        fgets(name, sizeof(name), user);
        for(i=0 ; i<sizeof(name) ; i++)
        {
            usersarray[k][i]=name[i];
        }
        k++;

    }
    memset(usersarray[k-1], '\0', sizeof(usersarray[k-1]));
    k=0;
    while(!feof(pass))
    {
        fgets(name, sizeof(name), pass);
        for(i=0 ; i<sizeof(name) ; i++)
        {
            passArray[k][i]=name[i];
        }
        k++;

    }
    memset(passArray[k-1], '\0', sizeof(passArray[k-1]));
    // close files.
    fclose(user);
    fclose(pass);

}
void RandomPassword()
{
    char random[20];
    srand(time(NULL));
    int i, k, r;
    for(i=0 ; i< 20 ; i++)
    {

        k = rand() % 1000;
        r = rand() % 52;
        if (k%2)
        {
            random[i] =  (r+65);
        }
        else
        {
            random[i] = (r%10 + '0');
        }
    }
    printf("\n%s\n\n", random);

}
void ModifyUser()
{
k:
    printf("What would you like to modify?\n1-Username\n2-Password\n");
    int n ;
    scanf("%d", &n);


    if (n==1)
    {
        printf("Enter new Username: ");
        char name[50];
        scanf("%s", name);
        strcat(name, "\n");
        memset(usersarray[logidx], '\0', sizeof(usersarray[logidx]));
        strcpy(usersarray[logidx], name);

        if ((user = fopen("Username.txt", "w") ) == NULL)
        {
            printf("an error happened while opening files\n");
            return 0;
        }
        fclose(user);
        if ((user = fopen("Username.txt", "a") ) == NULL)
        {
            printf("an error happened while opening files\n");
            return 0;
        }

        int i=0;
        while(usersarray[i] != '\0' && i<50)
        {
            fputs(usersarray[i], user);
            i++;
        }
        fclose(user);

    }

    else if (n==2)
    {
        printf("Enter new Password: ");
        char name[50];
        scanf("%s", name);
        strcat(name, "\n");
        memset(passArray[logidx], '\0', sizeof(passArray[logidx]));
        strcpy(passArray[logidx], name);

        if ((user = fopen("Pass.txt", "w") ) == NULL)
        {
            printf("an error happened while opening files\n");
            return 0;
        }
        fclose(pass);
        if ((user = fopen("Pass.txt", "a") ) == NULL)
        {
            printf("an error happened while opening files\n");
            return 0;
        }

        int i=0;
        while(passArray[i] != '\0' && i<50)
        {
            fputs(passArray[i], pass);
            i++;
        }
        printf("\n");
        fclose(pass);
    }
    else
    {
        printf("invalid choice\n");
        goto k;
    }
}
void DeleteUser()
{


    if (( (user = fopen("Username.txt", "w") ) == NULL) || ((pass= fopen("Pass.txt", "w")) == NULL) )
    {
        printf("an error happened while opening files\n");
        return 0;
    }
    fclose(user);
    fclose(pass);
    if (( (user = fopen("Username.txt", "a") ) == NULL )  || ( (pass = fopen("Pass.txt", "a")) == NULL ))
    {
        printf("an error happened while opening files\n");
        return 0;
    }
    int m=0;
    while(usersarray[m] != '\0' && passArray[m] != '\0' && m<50)
    {
        if(m==logidx)
        {
            m++;
            continue;
        }

        fputs(usersarray[m], user);
        fputs(passArray[m], pass);
        m++;
    }
    fclose(user);
    fclose(pass);

}
void UserFunctions()
{
k:
    printf("Select a function:\n1-Generate a random password\n2-Modify an existing user\n3-Delete account\n4-Logout\n\n");
    int p ;
    scanf("%d", &p);
    switch (p)
    {
    case 1:
        RandomPassword();
        break;
    case 2:
        ModifyUser();
        break;
    case 3:
        DeleteUser();
        break;
    case 4:
        return 0;
    default:
        printf("invalid input\n");
        goto k;
    }
}
void LogIn()
{
    GetFileData();
    char loginUser[50], loginPass[50];
    printf("Enter Username:");
    scanf("%s", loginUser);
    printf("Enter password:");
    scanf("%s",loginPass);
    int i=0;
    bool f = 1;
    for(i=0 ; i< 50 ; i++)
    {
        if (compare_string(loginUser, usersarray[i]) == 0  && compare_string( loginPass, passArray[i]) ==0 )
        {
            printf("Logged in successfully\n\n");
            logidx=i;
            f=false;
            break;
        }
    }
    if(f)
    {
        printf("Wrong login data.\n\n");
    }
    else
    {
        UserFunctions();
    }
}


int main()
{
b:
    printf("Select an option: \n1-Create account\n2-Log in\n3-Exit\n");
    int x ;
a:
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        CreateAccount();
        break;
    case 2:
        LogIn();
        break;
    case 3:
        return 0;
    default:
    {
        printf("Not valid choice\n");
        goto a;
    }

    }
    goto b;
}
