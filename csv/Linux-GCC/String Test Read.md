
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1382.45 | 0.116483 | 306.251ms | 4215 | 30 | 344.148 | 2907.7 | 0.192964 | 1.77321 | 1(Win) | true |
| Glaze | 975.185 | 0.139848 | 433.34ms | 4215 | 40 | 1329.2 | 4122.02 | 0.0127381 | 2.52302 | 2(Loss) | true |
| simdjson (reflection) | 955.793 | 0.265462 | 420.807ms | 4215 | 1280 | 159544 | 4205.66 | 0.0180342 | 2.57315 | 3(Loss) | true |
| simdjson (ondemand) | 687.068 | 0.178336 | 592.56ms | 4215 | 30 | 3265.84 | 5850.57 | 0.380322 | 3.58794 | 4(Loss) | true |
