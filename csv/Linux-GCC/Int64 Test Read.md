
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4619.96 | 0.0522798 | 791.519ms | 3862 | 640 | 111.172 | 797.212 | 0.116557 | 1.17285 | 6.65122 | 0.58493 | 0.00103573 | 3.19621e-05 | 2.02292e-06 | 1(Win) | true |
| simdjson (stage-1) | 1471.69 | 0.0430988 | 962.606ms | 3862 | 1280 | 1489.12 | 2502.62 | 0.184808 | 3.55725 | 17.9259 | 1.35811 | 0.000701749 | 2.913e-05 | 8.09166e-07 | 2(Loss) | true |
