
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 657.264 | 0.206193 | 9894.6ms | 264040 | 80 | 4.99228e+07 | 383116 | 0.128004 | 7.70924 | 28.633 | 5.43237 | 0.0240715 | 0.00200765 | 7.44205e-05 | 1(Win) | true |
| simdjson (ondemand) | 310.398 | 0.0976065 | 5137.42ms | 264040 | 320 | 2.00636e+08 | 811243 | 0.435585 | 16.2303 | 64.3159 | 13.0753 | 0.0894179 | 0.000395122 | 0.00014219 | 2(Loss) | true |
