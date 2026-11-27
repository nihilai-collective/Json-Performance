
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 810.748 | 0.190456 | 6729.97ms | 1834197 | 30 | 5.06559e+08 | 2.15755e+06 | 0.276368 | 3.05365 | 1(Win) | true |
| Jsonifier (two-stage) | 722.971 | 0.101095 | 7570.69ms | 1834197 | 80 | 4.78633e+08 | 2.4195e+06 | 0.0646419 | 3.4243 | 2(Loss) | true |
| Glaze | 645.357 | 0.199814 | 8451.3ms | 1834197 | 160 | 4.69313e+09 | 2.71048e+06 | 0.796283 | 3.83606 | 3(Loss) | true |
| simdjson (ondemand) | 554.528 | 0.289123 | 9623.3ms | 1834197 | 160 | 1.33085e+10 | 3.15444e+06 | 0.00945938 | 4.46435 | 4(Loss) | true |
