
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2841.47 | 0.0365662 | 132.742ms | 3862 | 160 | 35.9434 | 1296.19 | 0.0854189 | 0.852547 | 1(Win) | true |
| simdjson (stage-1) | 1384.56 | 0.0387407 | 266.828ms | 3862 | 80 | 84.9619 | 2660.11 | 0.0136291 | 1.77022 | 2(Loss) | true |
