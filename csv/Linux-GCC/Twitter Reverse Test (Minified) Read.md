
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 651.831 | 0.0412844 | 10028.9ms | 264040 | 1280 | 3.25574e+07 | 386309 | 0.0506957 | 7.8083 | 28.6322 | 5.43283 | 0.0265254 | 0.00079668 | 8.87857e-05 | 1(Win) | true |
| simdjson (ondemand) | 306.979 | 0.149127 | 5209.68ms | 264040 | 80 | 1.19708e+08 | 820278 | 0.0308626 | 16.48 | 64.3395 | 13.0848 | 0.0935266 | 0.00101978 | 0.000201106 | 2(Loss) | true |
