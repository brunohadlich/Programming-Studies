FROM node:20-alpine

COPY package.json .

RUN npm i

COPY . .

EXPOSE 80

CMD ["node", "app.js"]