//waitFor returns a promise
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
        //We do not await for its resolve
        return waitFor(seconds);
    });
    //Promise.all to sync the end of execution of all promises
    await Promise.all(promises);
    console.log("The end.")
})();
//==============================================================================
var p = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve(1);
    }, 2 * 1000);
});

//async functions when executed return a Promise
var p2 = async () => {
    throw new Error(1);
};

//Replace p by p2() to see the result
p.then((value) => {
    console.log("Success: ", value);
    return new Promise((resolve, reject) => {
        reject(2);
    });
}).catch((reason) => {
    console.log("Reason: ", reason);
    return new Promise((resolve, reject) => {
        resolve(3);
    });
}).then((value) => {
    console.log("Success: ", value);
});