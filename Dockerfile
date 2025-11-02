FROM ubuntu:24.04

# 기본 업데이트 및 개발도구
RUN apt update && apt install -y \
    gcc g++ \
    cmake \
    wget \
    curl && curl -LsSO https://r.mariadb.com/downloads/mariadb_repo_setup \
    && chmod +x mariadb_repo_setup \
    && ./mariadb_repo_setup \
    && apt install -y libmariadb3 libmariadb-dev

RUN ARCH=$(uname -m) && \
    if [ "$ARCH" = "aarch64" ]; then \
        wget https://dlm.mariadb.com/4464899/Connectors/cpp/connector-cpp-1.1.7/mariadb-connector-cpp_1.1.7-1+maria~noble_arm64.deb && \
        dpkg -i mariadb-connector-cpp_1.1.7-1+maria~noble_arm64.deb && \
        rm mariadb-connector-cpp_1.1.7-1+maria~noble_arm64.deb; \
    else \
        wget https://dlm.mariadb.com/4464930/Connectors/cpp/connector-cpp-1.1.7/mariadb-connector-cpp_1.1.7-1+maria~noble_amd64.deb && \
        dpkg -i mariadb-connector-cpp_1.1.7-1+maria~noble_amd64.deb && \
        rm mariadb-connector-cpp_1.1.7-1+maria~noble_amd64.deb; \
    fi && apt install -f

WORKDIR /app
COPY . .

RUN ./run.sh

CMD ["/bin/bash"]