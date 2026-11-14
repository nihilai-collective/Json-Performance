
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 26583.2 | 0.11127 | 1515.18ms | 213963 | 40 | 2917.95 | 7675.95 | 0.258365 | 0.194821 | 0.623014 | 0.145637 | 5.81876e-05 | 1.51895e-06 | 7.01056e-07 | 1(Win) | true |
| Glaze | 6348.78 | 0.072744 | 3964.15ms | 213963 | 4890 | 2.67301e+06 | 32140.2 | 0.136643 | 0.793943 | 3.56743 | 0.569169 | 0.000526276 | 7.08511e-06 | 4.75303e-06 | 2(Loss) | true |
| simdjson (reflection) | 476.481 | 0.237939 | 5553.27ms | 213963 | 640 | 6.64507e+08 | 428246 | 0.498712 | 10.4926 | 41.6907 | 8.45599 | 0.0418418 | 0.204248 | 0.000688181 | 3(Loss) | true |
