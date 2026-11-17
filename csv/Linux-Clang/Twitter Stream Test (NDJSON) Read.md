
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2015.97 | 0.675488 | 6968.97ms | 4219120 | 160 | 2.90824e+10 | 1.99589e+06 | 1.04068 | 1.22806 | 1(Win) | true |
| Jsonifier (generic) | 1944.75 | 0.179147 | 7345.92ms | 4219120 | 160 | 2.19815e+09 | 2.06899e+06 | 0.00701078 | 1.27296 | 2(Loss) | true |
