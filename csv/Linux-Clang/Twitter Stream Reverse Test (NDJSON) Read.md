
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.585 | 0.0738981 | 8273.84ms | 4219120 | 80 | 1.2099e+09 | 5.26255e+06 | 0.00157454 | 6.66123 | 26.4406 | 4.97297 | 0.0173897 | 0.0577318 | 0.00214198 | 1(Win) | true |
| simdjson (ondemand) | 296.564 | 0.0830157 | 9732.46ms | 4219120 | 40 | 5.07444e+09 | 1.35676e+07 | 0.571388 | 17.1072 | 70.1423 | 12.163 | 0.0794076 | 0.0552 | 0.00415004 | 2(Loss) | true |
