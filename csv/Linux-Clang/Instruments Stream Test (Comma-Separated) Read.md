
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1568.26 | 0.0563293 | 8096.08ms | 4197495 | 80 | 1.65388e+08 | 2.55254e+06 | 0.021777 | 1.57867 | 1(Win) | true |
| simdjson (ondemand) | 1220.43 | 0.061632 | 5050.92ms | 4197495 | 30 | 1.22598e+08 | 3.28001e+06 | 0.0105334 | 2.0286 | 2(Loss) | true |
