openssl genrsa -out private-key.pem 3072 && #generate private key
openssl rsa -in private-key.pem -pubout -out public-key.pem #generate a compatible public key for the private key int private-key.pem