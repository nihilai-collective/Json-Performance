
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1897.52 | 0.0827841 | 7404.28ms | 4219119 | 30 | 9.24452e+07 | 2.12048e+06 | 0.447523 | 1.30472 | 1(Win) | true |
| simdjson (ondemand) | 1863.67 | 0.0690403 | 7506.49ms | 4219119 | 30 | 6.66547e+07 | 2.159e+06 | 0.139176 | 1.32843 | 2(Loss) | true |
