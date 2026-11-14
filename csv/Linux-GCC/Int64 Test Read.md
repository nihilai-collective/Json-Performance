
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4237.25 | 0.0641137 | 795.077ms | 3862 | 4890 | 1518.68 | 869.217 | 0.0466055 | 1.27139 | 6.65122 | 0.58493 | 0.00103605 | 3.65895e-05 | 4.81859e-06 | 1(Win) | true |
| simdjson (stage-1) | 1467.69 | 0.125077 | 961.267ms | 3862 | 320 | 3152.53 | 2509.44 | 0.0124545 | 3.5614 | 17.9259 | 1.35811 | 0.000706402 | 3.56033e-05 | 1.61833e-06 | 2(Loss) | true |
