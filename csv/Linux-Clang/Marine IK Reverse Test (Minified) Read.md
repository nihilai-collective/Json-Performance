
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 801.239 | 0.121075 | 6793.31ms | 1834197 | 80 | 5.58938e+08 | 2.18315e+06 | 0.0415305 | 6.32109 | 26.9259 | 5.92556 | 0.0301554 | 0.0813295 | 0.00183885 | 1(Win) | true |
| Jsonifier (two-stage) | 734.395 | 0.0830034 | 7434.89ms | 1834197 | 160 | 6.2538e+08 | 2.38186e+06 | 0.370114 | 6.87638 | 31.6592 | 6.69969 | 0.0396764 | 0.145172 | 0.000819459 | 2(Loss) | true |
| Glaze | 691.119 | 0.134512 | 7877.87ms | 1834197 | 40 | 4.63626e+08 | 2.53101e+06 | 0.482615 | 7.27665 | 32.0086 | 6.49912 | 0.0355149 | 0.0815892 | 0.000167689 | 3(Loss) | true |
| simdjson (ondemand) | 590.849 | 0.1369 | 9249.74ms | 1834197 | 40 | 6.57063e+08 | 2.96053e+06 | 0.0339154 | 8.578 | 36.8602 | 6.23538 | 0.0412835 | 0.146824 | 0.000522259 | 4(Loss) | true |
