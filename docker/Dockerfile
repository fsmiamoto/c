FROM gcc:10.1.0 AS builder
WORKDIR /build
COPY . .
RUN make

FROM scratch
COPY --from=builder /build/server /bin/server
ENTRYPOINT ["/bin/server"]

