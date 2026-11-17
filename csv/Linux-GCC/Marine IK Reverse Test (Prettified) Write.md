
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.46 | 0.0661816 | 9509.92ms | 9930848 | 320 | 3.14703e+08 | 1.49844e+06 | 0.212657 | 0.795903 | 2.51822 | 0.147587 | 0.000345044 | 0.0249843 | 0.000271977 | 1(Win) | true |
| Glaze | 3635.74 | 0.143289 | 8162.21ms | 9930228 | 160 | 2.22885e+09 | 2.60475e+06 | 0.0512976 | 1.37527 | 4.41557 | 0.474372 | 0.000795399 | 0.041717 | 0.00261332 | 2(Loss) | true |
| simdjson (reflection) | 271.703 | 0.186526 | 10576.9ms | 10018896 | 30 | 1.29078e+11 | 3.51662e+07 | 0.143882 | 13.6451 | 38.7655 | 5.79716 | 0.0262146 | 0.268749 | 0.126208 | 3(Loss) | true |
