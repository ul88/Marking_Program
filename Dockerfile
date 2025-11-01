FROM alpine:latest

# 기본 업데이트 및 개발도구
RUN apk update && apk add --no-cache \
    build-base \
    gcc g++ \
    cmake \
    python3 python3-dev py3-pip \
    mariadb-connector-c-dev \
    mariadb-connector-c++ \
    mariadb-connector-c++-dev

WORKDIR /app
COPY . .

ENTRYPOINT ["./run.sh"]