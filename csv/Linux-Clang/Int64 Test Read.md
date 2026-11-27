
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 721.72 | 0.0790471 | 896.85ms | 1313 | 160 | 300.943 | 1734.99 | 0.295237 | 7.3035 | 36.4326 | 6.76923 | 0.000771135 | 0.000104722 | 0 | 1(Win) | true |
| simdjson (ondemand) | 375.64 | 0.0400056 | 1054.7ms | 1313 | 4890 | 8696.33 | 3333.44 | 0.0435339 | 13.809 | 56.6771 | 11.0312 | 0.000828587 | 0.000168209 | 4.78151e-05 | 2(Loss) | true |
