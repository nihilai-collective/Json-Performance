
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1893.03 | 0.0845652 | 7314.32ms | 4219120 | 160 | 5.1693e+08 | 2.12551e+06 | 0.0611128 | 2.67772 | 9.30168 | 1.57728 | 0.0167494 | 0.0535976 | 0.00101161 | 1(Win) | true |
| simdjson (ondemand) | 1774.86 | 0.245268 | 7765.37ms | 4219120 | 160 | 4.94672e+09 | 2.26703e+06 | 0.368968 | 2.83565 | 9.92054 | 1.52641 | 0.0144645 | 0.0538469 | 0.00174332 | 2(Loss) | true |
