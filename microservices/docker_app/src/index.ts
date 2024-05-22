import express from "express";
import readline from "readline";

// import * as cron from "node-cron";

// let counter = 0;

// cron.schedule("*/5 * * * * *", () => {
//     console.log(++counter);
// })

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
})
rl.on("line", (s) => {
    console.log(s);
})

const app = express();

const port = 8080;

app.get('/', (req: any, res: any) => {
    res.send("Hello world!");
})

app.listen(port, () => {
    console.log(`App listening on port ${port}.`)
})