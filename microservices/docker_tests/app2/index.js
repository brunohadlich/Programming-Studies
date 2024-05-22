const express = require("express")
const axios = require("axios")

const app = express()

const APP_1_PORT = process.env.APP_1_PORT

app.get("/", async (_, res) => {
    console.log(`Reaching App 1 on port ${APP_1_PORT}`)
    try {
        const response = (await axios.get(`http://app1_container:${APP_1_PORT}/`)).data
        console.log("Response", response)
        res.send(response)
    } catch (err) {
        console.error(err)
        res.send(err)
    }
})

const PORT = process.env.PORT

app.listen(PORT, () => {
    console.log(`App 2 listening on port ${PORT}`)
})