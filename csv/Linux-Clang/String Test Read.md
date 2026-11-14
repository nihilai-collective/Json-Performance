
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7029.23 | 0.103059 | 841.581ms | 9578 | 1280 | 2295.69 | 1299.47 | 0.0508362 | 0.755747 | 3.59626 | 0.338066 | 0.00102987 | 1.10931e-05 | 1.95761e-06 | 1(Win) | true |
| simdjson (stage-1) | 4297.26 | 0.0418143 | 924.046ms | 9578 | 1280 | 1011.17 | 2125.61 | 0.00701956 | 1.22163 | 5.95218 | 0.484861 | 0.00087856 | 1.01143e-05 | 3.26269e-07 | 2(Loss) | true |
