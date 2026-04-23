
#ifndef COMMON_H
#define COMMON_H

#define MSG_SIZE 128

typedef enum {
    MSG_START,
    MSG_GUESS,
    MSG_FEEDBACK,
    MSG_WIN,
    MSG_ERROR,
    MSG_EXIT
} MessageType;

typedef struct {
    int type;
    int guess[5];
    int feedback[5];
    int attempts;
    int winstatus;
    char message[MSG_SIZE];
} HackerMessage;

int palpite_valido(const char *entrada, int saida[5]);
void calcular_feedback(const int secret[5], const int guess[5], int feedback[5]);
void enviar_feedback(int client_socket, HackerMessage *msg, const int senha_secreta[5], int *contador_tentativas);
int recv_all(int sockfd, void *buf, int len);
int send_all(int sockfd, const void *buf, int len);

#endif
