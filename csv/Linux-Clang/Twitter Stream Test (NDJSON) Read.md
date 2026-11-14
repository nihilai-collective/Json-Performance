
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2010.8 | 0.0769873 | 6920.62ms | 4219120 | 160 | 3.79722e+08 | 2.00103e+06 | 0.911409 | 2.53597 | 9.28423 | 1.64402 | 0.011724 | 0.0570426 | 0.000339797 | 1(Win) | true |
| simdjson (ondemand) | 1755.79 | 0.0950217 | 7802.87ms | 4219120 | 80 | 3.79347e+08 | 2.29166e+06 | 0.0787248 | 2.86971 | 9.94023 | 1.53195 | 0.0156902 | 0.0546356 | 8.5074e-05 | 2(Loss) | true |
