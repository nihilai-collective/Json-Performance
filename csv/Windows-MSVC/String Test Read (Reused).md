
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.45 | 0.250627 | 511.473ms | 4215 | 30 | 3000 | 3990 | 0.333056 | 2.439 | 1(Win) | true |
| Glaze | 765.244 | 0.202838 | 633.417ms | 4215 | 4890 | 555141 | 5252.88 | 0.226441 | 3.21784 | 2(Loss) | true |
| simdjson (ondemand) | 505.31 | 0.0863196 | 918.847ms | 4215 | 80 | 3772.15 | 7955 | 0.157381 | 4.88477 | 3(Loss) | true |
