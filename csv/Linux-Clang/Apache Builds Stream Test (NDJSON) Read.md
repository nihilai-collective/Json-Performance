
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1861.41 | 0.0864693 | 8481.71ms | 4212000 | 40 | 1.39276e+08 | 2.15797e+06 | 0.173695 | 2.71797 | 11.4448 | 2.08984 | 0.0113275 | 0.0663459 | 0.00365432 | 1(Win) | true |
| simdjson (ondemand) | 1483.27 | 0.0651925 | 10244.6ms | 4212000 | 160 | 4.98716e+08 | 2.70813e+06 | 0.237651 | 3.41212 | 13.541 | 2.37315 | 0.0136181 | 0.0661918 | 0.00211212 | 2(Loss) | true |
