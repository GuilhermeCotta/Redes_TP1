#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     
#include <sys/types.h>
#include <sys/socket.h>

int palpite_valido(const char *entrada, int saida[5]) {
    if (strlen(entrada) != 5) {
        return -1;
    }
    for (int i = 0; i < 5; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            return -1;
        }
        saida[i] = entrada[i] - '0';
    }
    return 0;
}


void calcular_feedback(const int secret[5], const int guess[5], int feedback[5]) {
    int senha_usada[5] = {0, 0, 0, 0, 0};
    int palpite_processado[5] = {0, 0, 0, 0, 0}; 
    for (int i = 0; i < 5; i++) feedback[i] = 0;
    for (int i = 0; i < 5; i++) {
        if (guess[i] == secret[i]) {
            feedback[i] = 2;
            senha_usada[i] = 1;
            palpite_processado[i] = 1;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (palpite_processado[i]) continue; 

        for (int j = 0; j < 5; j++) {
            if (!senha_usada[j] && guess[i] == secret[j]) {
                feedback[i] = 1;
                senha_usada[j] = 1; 
                break;
            }
        }
    }
}

int recv_all(int sockfd, void *buf, int len) {
    char *ptr = (char *)buf;
    int total_lido = 0;
    int faltante = len;
    int n;

    while (total_lido < len) {
        n = recv(sockfd, ptr + total_lido, faltante, 0);
        
        if (n <= 0) {
            return n; 
        }

        total_lido += n;
        faltante -= n;
    }

    return total_lido; 
}

int send_all(int sockfd, const void *buf, int len) {
    const char *ptr = (const char *)buf;
    int total_enviado = 0;
    int faltante = len;
    int n;

    while (total_enviado < len) {
        n = send(sockfd, ptr + total_enviado, faltante, 0);

        if (n <= 0) {
            return n;
        }

        total_enviado += n;
        faltante -= n;
    }

    return total_enviado;
}

