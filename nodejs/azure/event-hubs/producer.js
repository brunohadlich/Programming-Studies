const { EventHubProducerClient } = require("@azure/event-hubs");

const connectionString = "";
const eventHubName = "tests-hub";

// Create a producer client to send messages to the event hub.
const producer = new EventHubProducerClient(connectionString, eventHubName, {retryOptions: {maxRetries: 3, maxRetryDelayInMs: 3000}});

let i = 1;

setInterval(async () => {
	const batch = await producer.createBatch({ partitionKey: i });
	for (let k = 0; k < 10; k++) {
		batch.tryAdd({ body: i + k });
	}

	// Send the batch to the event hub.
	await producer.sendBatch(batch);

	console.log(`Message '${i}' was sent to the event hub`);

	i += 10;
}, 3000);