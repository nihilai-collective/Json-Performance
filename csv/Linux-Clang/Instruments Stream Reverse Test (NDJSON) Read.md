
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1014.14 | 0.0729459 | 6102.84ms | 4197496 | 80 | 6.63244e+08 | 3.94721e+06 | 0.30344 | 4.99727 | 27.5614 | 5.67729 | 0.000924313 | 0.0817773 | 0.00210129 | 1(Win) | true |
| simdjson (ondemand) | 777.311 | 0.114152 | 7888.75ms | 4197496 | 40 | 1.38236e+09 | 5.14986e+06 | 0.0396799 | 6.51618 | 34.4591 | 5.37466 | 0.00789279 | 0.0811621 | 0.00603087 | 2(Loss) | true |
