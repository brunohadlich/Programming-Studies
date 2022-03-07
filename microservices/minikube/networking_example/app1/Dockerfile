FROM node:16-alpine

WORKDIR /app

COPY ./package.json .

RUN npm install

COPY . .

ARG PORT=8080
ENV PORT=${PORT}

EXPOSE ${PORT}

CMD ["npm", "run", "start"]