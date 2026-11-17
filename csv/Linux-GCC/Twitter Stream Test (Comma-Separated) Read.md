
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1803.57 | 0.241133 | 7868.63ms | 4219119 | 160 | 4.63031e+09 | 2.23094e+06 | 1.00407 | 1.37266 | 1(Win) | true |
| simdjson (ondemand) | 1761.34 | 0.122968 | 8011.86ms | 4219119 | 30 | 2.36735e+08 | 2.28443e+06 | 0.617483 | 1.40562 | 2(Loss) | true |
