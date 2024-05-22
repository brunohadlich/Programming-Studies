FROM node

WORKDIR /app

COPY package.json .

RUN npm i

COPY . .

ARG PORT=8000

ENV PORT=${PORT}

EXPOSE ${PORT}

CMD npm run main
