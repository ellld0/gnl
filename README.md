
Para rodar o teste local precisa descomentar o que está comentado no arquivo .h
# define read(fd, buffer, bytes) mock_read(fd, buffer, bytes)
size_t	mock_read(int fd, void *buf, size_t count);

Para rodar o teste da francinette precisa comentar no arquivo .h:
# define read(fd, buffer, bytes) mock_read(fd, buffer, bytes)
size_t	mock_read(int fd, void *buf, size_t count);
