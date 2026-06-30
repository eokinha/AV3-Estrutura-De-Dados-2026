#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "arquivo.h"
#include "util.h"

int main(){
    Pilha p;
    inicializarPilha(&p);
    carregarArquivo(&p);

    int opcao;

    do{
        printf("\n===== CHAMADAS DE EMERGENCIA =====\n");
        printf("1 - Registrar chamada\n2 - Atender chamada\n3 - Consultar ultima chamada\n4 - Listar chamadas\n0 - Sair\n");

        scanf("%d",&opcao);
        limparBuffer();

        switch(opcao){
            case 1:{
                Chamada c;
                printf("Protocolo: ");
                scanf("%d",&c.protocolo);
                limparBuffer();

                if(protocoloExiste(&p,c.protocolo)){
                    printf("Protocolo ja existe!\n");
                    break;
                }

                printf("Local: ");
                fgets(c.local,50,stdin);
                c.local[strcspn(c.local,"\n")] = '\0';

                printf("Tipo: ");
                fgets(c.tipo,30,stdin);
                c.tipo[strcspn(c.tipo,"\n")] = '\0';

                printf("Horario: ");
                fgets(c.horario,20,stdin);
                c.horario[strcspn(c.horario,"\n")] = '\0';

                push(&p,c);
                break;
            }
            case 2: pop(&p); break;
            case 3: peek(&p); break;
            case 4: listarChamadas(&p); break;
            case 0:
                salvarArquivo(&p);
                liberarPilha(&p);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}
