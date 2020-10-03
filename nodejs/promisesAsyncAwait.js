function waitFor(seconds) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            console.log(`${seconds} seconds later`);
            resolve();
        }, seconds * 1000);
    });
}

awaitSecondsList = [5, 3, 2, 7];

(async () => {
    //=======Non parallel execution of waitFor functions=======
    for (i in awaitSecondsList) {
        seconds = awaitSecondsList[i];
        await waitFor(seconds);
    }

    //=======Parallel execution of waitFor functions=======
    promises = awaitSecondsList.map((seconds) => {
        //waitFor returns a promise but we do not for its resolve
        //as before with await keyword
        return waitFor(seconds);
    });
    //Promise.all to sync the end of execution of all promises
    await Promise.all(promises);
    console.log("The end.")
})();