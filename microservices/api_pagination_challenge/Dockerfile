FROM node:16

ENV WD=/home/api/

WORKDIR ${WD}

COPY package.json package-lock.json ./

RUN ["npm", "install"]

COPY . ./

EXPOSE 8000/tcp

CMD npm run start