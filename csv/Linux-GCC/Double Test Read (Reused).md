
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 614.329 | 0.0768691 | 994.095ms | 1811 | 1280 | 5977.88 | 2811.36 | 0.15762 | 8.43031 | 40.3539 | 5.76532 | 0.00132912 | 9.18864e-05 | 1.03534e-05 | 1(Win) | true |
| simdjson (ondemand) | 338.785 | 0.0670485 | 1231.67ms | 1811 | 80 | 934.667 | 5097.94 | 0.0237785 | 15.3241 | 76.1817 | 9.53319 | 0.000738542 | 0.000110436 | 0 | 2(Loss) | true |
