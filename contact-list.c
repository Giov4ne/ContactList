#include <stdio.h>
#include <string.h>

#define LIMIT_OF_CONTACTS 100

typedef enum {TRUE, FALSE} Bool;
typedef enum {PERSONAL = 1, WORK} ContactType;

typedef struct{
    int id;
    char name[50];
    char phone[15];
    ContactType type;
} Contact;

void createContact(Contact contacts[], int *qty);
int getContactIndex(Contact contacts[], int qty, char phone[]);
void printContacts(Contact contacts[], int qty);
void findContact(Contact contacts[], int qty);
void deleteContact(Contact contacts[], int *qty);
void updateContact(Contact contacts[], int qty);

int main(){
    Contact contacts[LIMIT_OF_CONTACTS];
    int qty = 0, option;

    do{
        printf("\n======= MENU =======\n");
        printf("1- Cadastrar contato\n");
        printf("2- Excluir contato\n");
        printf("3- Editar contato\n");
        printf("4- Listar todos contatos\n");
        printf("5- Localizar contato\n");
        printf("6- Finalizar programa\n");
        printf("Opcao desejada: ");
        scanf("%d", &option);
        printf("\n");
        switch (option){
            case 1:
                createContact(contacts, &qty);
                break;
            case 2:
                deleteContact(contacts, &qty);
                break;
            case 3:
                updateContact(contacts, qty);
                break;
            case 4:
                printContacts(contacts, qty);
                break;
            case 5:
                findContact(contacts, qty);
                break;
            case 6:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!!\n");
                break;
        }
    } while (option != 6);

    return 0;
}

void createContact(Contact contacts[], int *qty){
    if (*qty >= LIMIT_OF_CONTACTS){
        printf("Limite de contatos atingido!!\n");
    } else{
        printf("Nome: ");
        scanf("%s", contacts[*qty].name);
        char phone[15];
        do{
            printf("Telefone: ");
            scanf("%s", phone);
            if (strlen(phone) < 11 || strlen(phone) > 14){
                printf("Numero de telefone invalido!!\n");
            } else if (getContactIndex(contacts, *qty, phone) >= 0){
                printf("Ja existe um contato cadastrado com este numero de telefone!!\n");
            }
        } while (strlen(phone) < 11 || strlen(phone) > 14 || getContactIndex(contacts, *qty, phone) >= 0);
        strcpy(contacts[*qty].phone, phone);
        do{
            printf("Tipo de contato [1-Pessoal; 2-Trabalho]: ");
            scanf("%d", &contacts[*qty].type);
            if (contacts[*qty].type < 1 || contacts[*qty].type > 2){
                printf("Tipo invalido! Digite 1 para Pessoal ou 2 para Trabalho\n");
            }
        } while (contacts[*qty].type < 1 || contacts[*qty].type > 2);
        contacts[*qty].id = ++(*qty);
        printf("Contato cadastrado com sucesso!!\n");
    }
}

int getContactIndex(Contact contacts[], int qty, char phone[]){
    for (int i = 0; i < qty; i++){
        if (strcmp(contacts[i].phone, phone) == 0){
            return i;
        }
    }
    return -1;
}

void printContacts(Contact contacts[], int qty){
    if (qty > 0){
        for (int i = 0; i < qty; i++){
            printf("========= Contato %d =========\n", contacts[i].id);
            printf("Nome: %s\n", contacts[i].name);
            printf("Telefone: %s\n", contacts[i].phone);
            printf("Tipo: %s", contacts[i].type == PERSONAL ? "Pessoal\n\n" : "Trabalho\n\n");
        }
    } else{
        printf("Nenhum contato cadastrado ate o momento!!\n");
    }
}

void findContact(Contact contacts[], int qty){
    if (qty > 0){
        char phone[15];
        do{
            printf("Telefone do contato a ser localizado: ");
            scanf("%s", phone);
            if (strlen(phone) < 11 || strlen(phone) > 14){
                printf("Numero de telefone invalido!!\n");
            }
        } while (strlen(phone) < 11 || strlen(phone) > 14);
        int index = getContactIndex(contacts, qty, phone);
        if (index >= 0){
            printf("\n========= Contato %d =========\n", contacts[index].id);
            printf("Nome: %s\n", contacts[index].name);
            printf("Telefone: %s\n", contacts[index].phone);
            printf("Tipo: %s", contacts[index].type == PERSONAL ? "Pessoal\n\n" : "Trabalho\n\n");
        } else{
            printf("Nao ha nenhum contato cadastrado com este telefone!!\n");
        }
    } else{
        printf("Nenhum contato cadastrado ate o momento!!\n");
    }
}

void deleteContact(Contact contacts[], int *qty){
    if (*qty > 0){
        char phone[15];
        do{
            printf("Telefone do contato a ser excluido: ");
            scanf("%s", phone);
            if (strlen(phone) < 11 || strlen(phone) > 14){
                printf("Numero de telefone invalido!!\n");
            }
        } while (strlen(phone) < 11 || strlen(phone) > 14);
        int index = getContactIndex(contacts, *qty, phone);
        if (index >= 0){
            int confirm;
            do{
                printf("Tem certeza que deseja excluir %s da sua lista de contatos?\n", contacts[index].name);
                printf("1- Sim\n");
                printf("2- Nao\n");
                printf("Opcao: ");
                scanf("%d", &confirm);
                if (confirm < 1 || confirm > 2){
                    printf("Opcao invalida!!\n");
                }
            } while (confirm < 1 || confirm > 2);
            if (confirm == 1){
                (*qty)--;
                for (int i = index; i < *qty; i++){
                    contacts[i].id = contacts[i + 1].id - 1;
                    strcpy(contacts[i].name, contacts[i + 1].name);
                    strcpy(contacts[i].phone, contacts[i + 1].phone);
                    contacts[i].type = contacts[i + 1].type;
                }
                printf("Contato excluido com sucesso!!\n");
            } else{
                printf("Acao cancelada!!\n");
            }
        } else{
            printf("Nao ha nenhum contato cadastrado com este telefone!!\n");
        }
    } else{
        printf("Nenhum contato cadastrado ate o momento!!\n");
    }
}

void updateContact(Contact contacts[], int qty){
    if (qty > 0){
        char phone[15];
        do{
            printf("Telefone do contato a ser editado: ");
            scanf("%s", phone);
            if (strlen(phone) < 11 || strlen(phone) > 14){
                printf("Numero de telefone invalido!!\n");
            }
        } while (strlen(phone) < 11 || strlen(phone) > 14);
        int index = getContactIndex(contacts, qty, phone);
        if (index >= 0){
            printf("Contato %d - %s\n\n", contacts[index].id, contacts[index].name);
            int editOption;
            do{
                printf("Campo a ser alterado: \n");
                printf("1- Nome\n");
                printf("2- Telefone\n");
                printf("3- Tipo de contato\n");
                printf("4- Cancelar edicao\n");
                printf("Opcao: ");
                scanf("%d", &editOption);
                switch (editOption){
                    case 1:
                        printf("\nNome atual: %s\n", contacts[index].name);
                        printf("Novo nome: ");
                        scanf("%s", contacts[index].name);
                        printf("Nome alterado com sucesso!!\n");
                        break;
                    case 2:{
                        char newPhone[15];
                        printf("\nTelefone atual: %s\n", contacts[index].phone);
                        do{
                            printf("Novo telefone: ");
                            scanf("%s", newPhone);
                            if (strlen(newPhone) < 11 || strlen(newPhone) > 14){
                                printf("Numero de telefone invalido!!\n");
                            }
                        } while(strlen(newPhone) < 11 || strlen(newPhone) > 14);
                        Bool phoneInUse = FALSE;
                        for(int i = 0; i < qty; i++){
                            if(i != index && strcmp(contacts[i].phone, newPhone) == 0){
                                phoneInUse = TRUE;
                                break;
                            }
                        }
                        if(phoneInUse == TRUE){
                            printf("Edicao cancelada!!\n");
                            printf("Ja existe um contato cadastrado com este numero de telefone!!\n");
                        } else{
                            strcpy(contacts[index].phone, newPhone);
                            printf("Telefone alterado com sucesso!!\n");
                        }
                        break;
                    }
                    case 3:
                        printf("\nTipo de contato atual: %s", contacts[index].type == PERSONAL ? "Pessoal\n" : "Trabalho\n");
                        int typeOption;
                        do{
                            printf("Trocar tipo de contato para %s?\n", contacts[index].type == PERSONAL ? "Trabalho" : "Pessoal");
                            printf("1- Sim\n");
                            printf("2- Nao\n");
                            printf("Opcao: ");
                            scanf("%d", &typeOption);
                            if(typeOption < 1 || typeOption > 2){
                                printf("Opcao invalida!!\n");
                            }
                        } while (typeOption < 1 || typeOption > 2);
                        if(typeOption == 1){
                            contacts[index].type = contacts[index].type == PERSONAL ? WORK : PERSONAL;
                            printf("Tipo de contato alterado com sucesso!!\n");
                        } else{
                            printf("Edicao cancelada!!\n");
                        }
                        break;
                    case 4:
                        printf("Edicao cancelada!!\n");
                        break;
                    default:
                        printf("Opcao invalida!!\n");
                        break;
                }
            } while (editOption < 1 || editOption > 4);
        } else{
            printf("Nao ha nenhum contato cadastrado com este telefone!!\n");
        }
    } else{
        printf("Nenhum contato cadastrado ate o momento!!\n");
    }
}