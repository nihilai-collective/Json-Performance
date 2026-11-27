
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3134.31 | 0.215176 | 7179.34ms | 1834197 | 320 | 4.61474e+08 | 558090 | 0.226974 | 1.61711 | 8.57463 | 1.61618 | 0.0057344 | 0.113104 | 6.08747e-06 | 1(Win) | true |
| simdjson (ondemand) | 2456.84 | 0.0889832 | 9184.11ms | 1834197 | 640 | 2.56882e+08 | 711982 | 0.119864 | 2.06863 | 12.8396 | 2.27677 | 0.00336086 | 0.150434 | 4.69722e-06 | 2(Loss) | true |
