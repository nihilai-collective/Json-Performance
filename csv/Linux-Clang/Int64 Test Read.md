
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5256.69 | 0.133658 | 781.343ms | 3862 | 640 | 561.271 | 700.648 | 0.0955789 | 1.03616 | 5.31978 | 0.535474 | 0.00129467 | 3.35804e-05 | 6.06875e-06 | 1(Win) | true |
| simdjson (stage-1) | 1921.61 | 0.0510862 | 903.949ms | 3862 | 4890 | 4688.25 | 1916.67 | 0.0359382 | 2.7296 | 14.3553 | 1.15148 | 0.000646645 | 2.97058e-05 | 1.5356e-06 | 2(Loss) | true |
