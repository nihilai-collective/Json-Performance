
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1136.06 | 0.144297 | 9889.88ms | 461466 | 640 | 1.99971e+08 | 387380 | 0.0691148 | 2.17902 | 1(Win) | true |
| Jsonifier | 1104.56 | 0.23298 | 5109.04ms | 461466 | 40 | 3.44666e+07 | 398428 | 0.0735434 | 2.24126 | 2(Loss) | true |
| simdjson (ondemand) | 1064.4 | 0.10761 | 5243.9ms | 461466 | 320 | 6.33472e+07 | 413462 | 0.444256 | 2.32581 | 3(Loss) | true |
| Jsonifier (two-stage) | 1027.62 | 0.0583342 | 5477.29ms | 461466 | 640 | 3.99429e+07 | 428259 | 0.129449 | 2.40907 | 4(Loss) | true |
| Glaze | 1008.46 | 0.0921614 | 5568.34ms | 461466 | 640 | 1.03523e+08 | 436395 | 0.157328 | 2.45482 | 5(Loss) | true |
