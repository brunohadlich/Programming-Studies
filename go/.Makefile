all:
	go build --ldflags '-linkmode external -extldflags "-static"' go_simple_api.go
