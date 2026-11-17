
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4301.98 | 0.111613 | 942.597ms | 9578 | 640 | 3594.37 | 2123.28 | 0.505227 | 1.20709 | 5.06786 | 1.0023 | 0.001547 | 1.41927e-05 | 9.78806e-07 | 1(Win) | true |
| Glaze | 1919.12 | 0.326122 | 1200.21ms | 9578 | 30 | 7228.17 | 4759.63 | 0.305808 | 2.65809 | 13.3883 | 2.61067 | 0.0018097 | 1.04406e-05 | 0 | 2(Loss) | true |
