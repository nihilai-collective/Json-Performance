
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2148.78 | 0.0917819 | 6656.38ms | 4219120 | 40 | 1.1815e+08 | 1.87254e+06 | 0.241228 | 1.15217 | 1(Win) | true |
| Jsonifier (generic) | 1863.19 | 0.157823 | 7572.81ms | 4219120 | 40 | 4.64656e+08 | 2.15956e+06 | 0.298505 | 1.32878 | 2(Loss) | true |
