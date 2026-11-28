
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1366.54 | 0.4417 | 87.6709ms | 1213 | 2560 | 35791 | 846.523 | 0.0877517 | 1.75648 | 1(Win) | true |
| Glaze | 420.148 | 0.336469 | 281.322ms | 1213 | 30 | 2574.71 | 2753.33 | 0.120919 | 5.79437 | 2(Loss) | true |
| simdjson (ondemand) | 309.307 | 0.20975 | 380.493ms | 1213 | 40 | 2461.54 | 3740 | 0.266667 | 8.01371 | 3(Loss) | true |
