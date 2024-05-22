FROM node

WORKDIR /app

COPY package.json .

RUN npm i

COPY . .

ENV APP_1_PORT=8000

ARG PORT=8001

ENV PORT=${PORT}

EXPOSE ${PORT}

CMD npm run main