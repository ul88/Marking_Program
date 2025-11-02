### 지원 언어
  - c
  - cpp
  - python

### 마킹프로그램 시작하기
```bash
mkdir marking_program && cd marking_program
git clone https://github.com/ul88/Marking_Program.git .

docker compose up db -d
docker compose run -rm marker ./compile.sh cpp 1 ul88 < ./test
```
이때, compile.sh의 첫 번째 인자는 컴파일할 언어의 확장자,
두 번째 인자는 문제의 번호 즉, test.problem 테이블의 id값
세 번째 인자는 사용자 이름으로 아무 이름을 사용해도 상관 없다.
마지막으로 표준 입력을 이용해서 파일을 읽으므로,
코드를 작성한 파일을 하나 생성하여 연결해준다.

```sql
INSERT INTO test.problem
VALUE (1);

INSERT INTO test.input
VALUE (1, 1, "");

INSERT INTO test.output
VALUE (1, 1, "Hello World!");
```
db 컨테이너에 접속하여 다음과 같은 쿼리문을 실행

```bash
vim ./test
```

```cpp
#include<iostream>
using namespace std;
int main()
{
  cout<<"Hello World!";
  return 0;
}
```

```bash
docker compose run -rm marker ./compile.sh cpp 1 ul88 < ./test
```
#### [output]
```bash
[+] Creating 1/1
 ✔ Container marking_program-db-1  Running                                                                                                                                                                                                               0.0s 
problem id( 1 )  correct!
```


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
    depends_on:
      - db
    environment:
      - DB_URL=jdbc:mariadb://db:3306/
      - DB_DATABASE=test
      - DB_NAME=root
      - DB_PASSWORD=1234 # 비밀번호 변경 항상 MARIADB_ROOT_PASSWORD와 동일해야 함
```

DB 설정을 수정은 ./db/docker-entrypoint-initdb.d/create_table.sql에서 진행

### 테이블 정보

<img width="935" height="312" alt="Copy of Untitled Diagram" src="https://github.com/user-attachments/assets/3fe91a2a-f3fa-4834-ad63-3ecda3bc0c29" />
