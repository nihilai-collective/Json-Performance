
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 17616.7 | 0.197112 | 5596.22ms | 16197086 | 30 | 8.96132e+07 | 876822 | 0.11198 | 0.28984 | 1.33568 | 0.070273 | 7.88599e-05 | 0.0157217 | 0.00215358 | 1(Win) | true |
| simdjson (ondemand) | 16712 | 0.368807 | 6051.2ms | 16197086 | 30 | 3.48608e+08 | 924290 | 0.349107 | 0.303765 | 1.26202 | 0.0749453 | 0.000116634 | 0.0157316 | 0.00139189 | 2(Loss) | true |
