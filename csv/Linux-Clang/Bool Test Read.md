
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1878.7 | 0.138301 | 47.0822ms | 905 | 30 | 12.1103 | 459.4 | 0.079878 | 1.24475 | 1(Win) | true |
| Glaze | 1465.65 | 0.127115 | 63.6648ms | 905 | 30 | 16.8092 | 588.867 | 0.00566091 | 1.61068 | 2(Loss) | true |
| simdjson (ondemand) | 452.186 | 0.070126 | 185.511ms | 905 | 40 | 71.6609 | 1908.67 | 0.0423684 | 5.39892 | 3(Loss) | true |
