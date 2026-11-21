
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4635.67 | 0.0718909 | 201.532ms | 9578 | 160 | 321.065 | 1970.44 | 0.0139582 | 0.527338 | 1(Win) | true |
| Glaze | 2005.19 | 0.207847 | 461.67ms | 9578 | 1280 | 114745 | 4555.32 | 0.454193 | 1.22776 | 2(Loss) | true |
