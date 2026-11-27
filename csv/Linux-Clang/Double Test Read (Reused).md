
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.969 | 0.0488281 | 941.52ms | 1811 | 4890 | 6069.17 | 2281.61 | 0.0307792 | 6.91008 | 35.2435 | 7.32965 | 0.0011134 | 8.88684e-05 | 1.53572e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.813 | 0.0530911 | 1122.25ms | 1811 | 1280 | 5271.98 | 3822.61 | 0.0750213 | 11.5261 | 58.2435 | 11.2082 | 0.00222123 | 8.88666e-05 | 1.29417e-05 | 2(Loss) | true |
