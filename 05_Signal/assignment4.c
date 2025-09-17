//LESSON 5 - ASSIGNMENT 4
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
 
#define BUFFER_SIZE 1024
 
volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;
 
// Signal handler cho SIGINT
void sigint_handler(int signum) {
    sigint_received = 1;
}
 
// Signal handler cho SIGTERM
void sigterm_handler(int signum) {
    sigterm_received = 1;
}
 
int main() {
    fd_set read_fds;
    char buffer[BUFFER_SIZE];
    int stdin_fd = STDIN_FILENO; // File descriptor cho standard input
 
    // Thiết lập signal handlers
    struct sigaction sa_int, sa_term;
 
    memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
 
    memset(&sa_term, 0, sizeof(sa_term));
    sa_term.sa_handler = sigterm_handler;
    sigemptyset(&sa_term.sa_mask);
    sa_term.sa_flags = 0;
    if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
        perror("sigaction SIGTERM");
        exit(EXIT_FAILURE);
    }
 
    printf("Nhập liệu vào console (nhấn Ctrl+C để nhận SIGINT, hoặc gửi SIGTERM để thoát).\n");
 
    while (1) {
        // Reset fd_set
        FD_ZERO(&read_fds);
        FD_SET(stdin_fd, &read_fds);
 
        // Thiết lập thời gian chờ cho select (có thể là NULL để chờ vô hạn)
        struct timeval timeout;
        timeout.tv_sec = 1; // Chờ 1 giây
        timeout.tv_usec = 0;
 
        // Gọi select()
        int activity = select(stdin_fd + 1, &read_fds, NULL, NULL, &timeout);
 
        if (activity < 0) {
            // Kiểm tra xem có phải do tín hiệu ngắt hay không
            if (errno == EINTR) {
                // Tín hiệu đã được nhận. Kiểm tra xem đó là SIGINT hay SIGTERM.
                if (sigint_received) {
                    printf("\nSIGINT received.\n");
                    sigint_received = 0;
                }
                if (sigterm_received) {
                    printf("SIGTERM received. Exiting.\n");
                    exit(EXIT_SUCCESS); // Thoát chương trình
                }
                // Nếu là tín hiệu khác làm gián đoạn, tiếp tục vòng lặp
                continue;
            } else {
                // Lỗi khác của select
                perror("select");
                exit(EXIT_FAILURE);
            }
        } else if (activity > 0) {
            // Có hoạt động trên file descriptor
            if (FD_ISSET(stdin_fd, &read_fds)) {
                // Có dữ liệu nhập từ bàn phím
                ssize_t bytes_read = read(stdin_fd, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0'; // Đảm bảo là chuỗi kết thúc bằng null
                    printf("Bạn đã nhập: %s", buffer);
                    // Nếu buffer chứa ký tự xuống dòng, nó sẽ được in ra bởi printf
                    // Nếu không, bạn có thể cần thêm `fflush(stdout);`
                } else if (bytes_read == 0) {
                    // End of file (ví dụ: Ctrl+D)
                    printf("End of input detected. Exiting.\n");
                    exit(EXIT_SUCCESS);
                } else {
                    // Lỗi khi đọc
                    perror("read");
                    exit(EXIT_FAILURE);
                }
            }
        }
        // Nếu activity == 0, nghĩa là timeout, không có gì xảy ra, vòng lặp tiếp tục.
    }
 
    return 0;
}