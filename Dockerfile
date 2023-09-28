FROM gcc:4.9
COPY . /usr/src/app
WORKDIR /usr/src/app
RUN gcc -o loto loto.c
CMD ["./loto"]