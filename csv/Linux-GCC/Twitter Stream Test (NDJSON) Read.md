
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2019.41 | 0.273295 | 6987.06ms | 4219120 | 160 | 4.74436e+09 | 1.99249e+06 | 0.146993 | 2.49557 | 9.1929 | 1.59761 | 0.0146913 | 0.0572806 | 0.000462245 | 1(Win) | true |
| simdjson (ondemand) | 1817.25 | 0.364996 | 7643.85ms | 4219120 | 80 | 5.22491e+09 | 2.21415e+06 | 0.0696555 | 2.7728 | 9.42865 | 1.53537 | 0.0157463 | 0.0543795 | 0.000380198 | 2(Loss) | true |
