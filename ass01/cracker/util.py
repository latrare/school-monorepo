def chunk(chunkable, size):
    for index in range(0, len(chunkable), size):
        yield chunkable[index:index + size]
