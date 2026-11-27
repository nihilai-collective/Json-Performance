
----
### Instruments Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6846.96 | 0.0962044 | 3304.84ms | 183677 | 160 | 96922.4 | 25583.3 | 0.0992841 | 0.752471 | 3.79782 | 0.533894 | 0.00057499 | 4.83185e-06 | 3.36869e-06 | 1(Win) | true |
| simdjson (ondemand) | 6223.21 | 0.0249753 | 3540.26ms | 183677 | 2560 | 126515 | 28147.5 | 0.221945 | 0.816729 | 4.09533 | 0.473119 | 0.00119621 | 3.87484e-06 | 2.42231e-06 | 2(Loss) | true |
