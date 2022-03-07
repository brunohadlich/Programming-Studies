FROM node:16-alpine

WORKDIR /app

COPY ./package.json .

RUN npm install

COPY . .

ARG PORT=8081

ENV PORT=${PORT}

ARG API_HOST=foobarxpto

ENV API_HOST=${API_HOST}

ARG API_PORT=8080

ENV API_PORT=${API_PORT}

EXPOSE ${PORT}

CMD ["npm", "run", "start"]