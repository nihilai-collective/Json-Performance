
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2005.08 | 0.114741 | 7213.21ms | 4219120 | 40 | 2.1207e+08 | 2.00673e+06 | 0.736382 | 1.23474 | 1(Win) | true |
| simdjson (ondemand) | 1980.7 | 0.0846594 | 7170.88ms | 4219120 | 160 | 4.73237e+08 | 2.03144e+06 | 0.325422 | 1.24994 | 2(Loss) | true |
