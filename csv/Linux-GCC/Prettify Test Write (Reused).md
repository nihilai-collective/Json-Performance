
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5502.78 | 0.519402 | 6560.47ms | 699405 | 30 | 1.18911e+07 | 121212 | 0.671871 | 0.449801 | 1(Win) | true |
| Glaze | 3409.09 | 0.117319 | 5178.84ms | 699405 | 160 | 8.43015e+06 | 195655 | 0.077102 | 0.726133 | 2(Loss) | true |
| simdjson (ondemand) | 2703 | 0.173011 | 7028.16ms | 767297 | 80 | 1.75498e+07 | 270719 | 0.0634297 | 0.915841 | 3(Loss) | true |
