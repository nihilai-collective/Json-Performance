
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1335.04 | 0.0264314 | 4563.83ms | 53331 | 4890 | 495817 | 38096.5 | 0.0902303 | 3.81862 | 13.3854 | 2.60854 | 0.0120944 | 0.000157077 | 0.000116708 | 1(Win) | true |
| simdjson (ondemand) | 1027.44 | 0.0391556 | 5681.27ms | 53331 | 2560 | 961787 | 49502.3 | 0.130778 | 4.95474 | 17.7272 | 3.48605 | 0.0201827 | 0.00013401 | 9.32267e-05 | 2(Loss) | true |
