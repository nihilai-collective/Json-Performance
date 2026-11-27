
----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.708 | 0.0554262 | 10018ms | 360584 | 1280 | 5.82186e+07 | 384778 | 0.0850251 | 5.70824 | 21.136 | 3.90759 | 0.022232 | 0.00460735 | 6.51894e-05 | 1(Win) | true |
| simdjson (ondemand) | 433.807 | 0.13078 | 5054.82ms | 360584 | 160 | 1.71959e+08 | 792702 | 0.11948 | 11.6067 | 46.8452 | 9.4512 | 0.0529534 | 0.00377767 | 8.40997e-05 | 2(Loss) | true |
