#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mesa.h"
#include "fila.h"
#include "pratos.h"

void esperar_enter()
{
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}

Fila *arrumar_mesa(Fila *fila, Mesa *mesas, Pilha **pratos)
{
    Mesa *m;
    m = mesa_a_arrumar(mesas);
    if (m != NULL)
    {
        *pratos = pratos_arrumar_mesa(*pratos, m);
        if (m->pratos == 4)
        {
            if (fila != NULL)
            {
                if (fila->pessoas > 4)
                {
                    printf("Foi encontrado uma mesa para 4 membros do primeiro grupo da fila!!\n");
                    printf("Ainda ficaram %d na Fila de Espera!!\n", fila->pessoas);
                    m->pessoas_sentadas = 4;
                }
                else
                {
                    printf("Foi encontrado uma mesa para o restante do primeiro grupo da fila!!\n");
                    m->pessoas_sentadas = fila->pessoas;
                }
                m->livre = false;
                fila = fila_mesa_encontrada(fila);
            }
            else
            {
                m->livre = true;
            }
        }
    }
    return fila;
}

void imprimir_relatorios(int escolha, Mesa *mesas, Fila *fila, Pilha *pratos)
{
    switch (escolha)
    {
    case 1:
        mesa_pesquisar(mesas);
        break;
    case 2:
        mesa_listar(mesas);
        break;
    case 3:
        fila_numero_de_grupo(fila);
        break;
    case 4:
        fila_quant_pessoas(fila);
        break;
    case 5:
        pratos_imprimir(pratos);
        break;
    default:
        break;
    }
}

void menu_relatorios(Mesa *mesas, Fila *fila, Pilha *pratos)
{
    int escolha;
    printf("RELATORIOS\n");

    printf("1. Pesquisar mesa.\n");
    printf("2. Listar todas mesas.\n");
    printf("3. Listar numero de grupos na fila.\n");
    printf("4. Listar quantidade de pessoas na fila.\n");
    printf("5. Listar quantidade de pratos.\n");

    printf("6. Voltar.\n");
    do
    {
        printf("Digite o numero do que deseja imprimir:");
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > 6)
        {
            printf("POR FAVOR DIGITE UM NUMERO VALIDO!\n");
            break;
        }
        printf("\n");
    } while (escolha < 1 || escolha > 6);
    imprimir_relatorios(escolha, mesas, fila, pratos);
}

void menu_opcoes(int escolha, Mesa **mesas, Fila **fila, Pilha **pratos)
{
    Mesa *m;
    switch (escolha)
    {
    case 1:
        *fila = chegar_grupo(*mesas, *fila);
        break;

    case 2:
        *mesas = mesa_liberar(*mesas);
        break;

    case 3:
        *fila = fila_sair(*fila);
        break;

    case 4:
        *fila = arrumar_mesa(*fila, *mesas, pratos);
        break;

    case 5:
        *pratos = repor_pratos(*pratos);
        break;

    case 6:
        menu_relatorios(*mesas, *fila, *pratos);
        break;

    default:
        break;
    }
    esperar_enter();
}

void menu(Mesa *mesas, Fila *fila, Pilha *pratos)
{
    char sair;
    int escolha;
    do
    {
        printf("MENU\n");

        printf("1. Chegada de Cliente\n");
        printf("2. Liberar Mesa\n");
        printf("3. Desistir de Esperar\n");
        printf("4. Arrumar Mesa\n");
        printf("5. Repor pratos\n");
        printf("6. Imprimir Pilha, Fila de espera e Ocupacao de mesa\n");

        printf("7. Sair\n");

        do
        {
            printf("DIGITE O NUMERO DO QUE DESEJA REALIZAR:");
            scanf("%d", &escolha);
            if (escolha < 1 || escolha > 7)
            {
                printf("POR FAVOR DIGITE UM NUMERO VALIDO!\n");
                break;
            }
            printf("\n");
        } while (escolha < 1 || escolha > 7);

        menu_opcoes(escolha, &mesas, &fila, &pratos);

    } while (escolha != 7);
}

int main()
{
    Mesa *restaurante = inicializa_mesas();
    Fila *fila = fila_criar();
    Pilha *pratos = pilha_criar();
    menu(restaurante, fila, pratos);
}