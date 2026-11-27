
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8556.79 | 0.462259 | 750.08ms | 2963 | 30 | 69.9092 | 330.233 | 0.12098 | 0.683643 | 1.57746 | 0.229497 | 0.000337496 | 2.24997e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7208.47 | 0.208867 | 759.881ms | 2963 | 1280 | 858.082 | 392.002 | 0.135537 | 0.785744 | 1.7948 | 0.270672 | 0.000337759 | 4.90424e-05 | 8.43739e-06 | 2(Loss) | true |
| Glaze | 5654.58 | 0.54365 | 767.453ms | 2963 | 40 | 295.23 | 499.725 | 0.134892 | 0.984568 | 2.99224 | 0.462707 | 0.000345933 | 7.59366e-05 | 2.53122e-05 | 3(Loss) | true |
