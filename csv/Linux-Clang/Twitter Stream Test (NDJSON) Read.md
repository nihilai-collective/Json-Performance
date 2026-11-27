
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2225.92 | 0.05187 | 6437.87ms | 4219120 | 80 | 7.03313e+07 | 1.80764e+06 | 0.0280451 | 1.11224 | 1(Win) | true |
| Jsonifier (generic) | 2091.79 | 0.041635 | 6770.82ms | 4219120 | 40 | 2.56556e+07 | 1.92355e+06 | 0.11382 | 1.18355 | 2(Loss) | true |
