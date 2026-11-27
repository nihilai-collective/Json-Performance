
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.38 | 0.721877 | 8152.41ms | 4212000 | 40 | 8.57569e+09 | 2.02834e+06 | 0.736056 | 2.54993 | 10.8643 | 1.97769 | 0.0137817 | 0.0666297 | 0.0113668 | 1(Win) | true |
| simdjson (ondemand) | 1545.66 | 0.0908918 | 9980.17ms | 4212000 | 160 | 8.92733e+08 | 2.59882e+06 | 0.105377 | 3.28282 | 12.612 | 2.34621 | 0.0132072 | 0.0668903 | 0.00458646 | 2(Loss) | true |
