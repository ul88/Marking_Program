### 지원 언어
  - c
  - cpp
  - python

### 마킹프로그램 시작하기
```bash
mkdir marking_program && cd marking_program
git clone https://github.com/ul88/Marking_Program.git .

docker compose up db -d
docker compose run -rm marker ./compile.sh 1 ul88
```
이때, compile.sh의 첫 번째 인자는 문제의 번호 즉, test.problem 테이블의 id값
두 번째 인자는 사용자 이름으로 아무 이름을 사용해도 상관 없다.

### 환경 설정

docker-compose.yml 수정
```bash
services:
  db:
    image: mariadb
    restart: always
    environment:
      - MARIADB_DATABASE=test
      - MARIADB_ROOT_PASSWORD=1234
    volumes:
      - ./db/conf.d:/etc/mysql/conf.d
      - ./db/docker-entrypoint-initdb.d:/docker-entrypoint-initdb.d
    ports:
      - 4999:3306
  
  marker:
    container_name: marker
    build:
      context: .
      dockerfile: Dockerfile
    restart: 'no'
    stdin_open: true
    tty: true
    depends_on:
      - db
    ports:
      - 5000:5000
    environment:
      - DB_URL=jdbc:mariadb://db:3306/
      - DB_DATABASE=test
      - DB_NAME=root
      - DB_PASSWORD=1234 # 비밀번호 변경 항상 MARIADB_ROOT_PASSWORD와 동일해야 함
```

DB 설정을 수정은 ./db/docker-entrypoint-initdb.d/create_table.sql에서 진행

실행하고자 하는 코드 파일은
./marking/resource 에 main 이름으로 저장

### 테이블 정보

<img width="935" height="312" alt="Copy of Untitled Diagram" src="https://github.com/user-attachments/assets/3fe91a2a-f3fa-4834-ad63-3ecda3bc0c29" />
