const express = require("express")

const app = express()

app.get("/", (_, res) => {
    const MSG = "Hello world from app 1."
    res.send(MSG)
    console.log("Replied", MSG)
})

const PORT = process.env.PORT

app.listen(PORT, () => {
    console.log(`App 1 listening on port ${PORT}`)
})