
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2270.99 | 0.0719022 | 8139.59ms | 360584 | 640 | 7.58662e+06 | 151423 | 0.149944 | 2.24682 | 7.75498 | 1.3465 | 0.0106968 | 0.000873418 | 2.87034e-05 | 1(Win) | true |
| simdjson (ondemand) | 2231.13 | 0.0648421 | 8247.86ms | 360584 | 1280 | 1.27847e+07 | 154128 | 0.0945565 | 2.25744 | 8.1897 | 1.35482 | 0.00705737 | 0.0027365 | 4.0869e-05 | 2(Loss) | true |
