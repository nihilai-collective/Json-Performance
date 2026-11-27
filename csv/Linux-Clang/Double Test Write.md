
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 370.399 | 0.170474 | 1267.27ms | 1997 | 640 | 49171.6 | 5141.72 | 0.00714185 | 14.015 | 58.2233 | 10.346 | 0.0190606 | 0.000116581 | 2.42551e-05 | 1(Win) | true |
| Glaze | 304.966 | 0.285774 | 1290.05ms | 1798 | 320 | 82617.3 | 5622.61 | 0.0582131 | 17.0024 | 71.2831 | 12.1485 | 0.021882 | 0.000119925 | 1.91185e-05 | 2(Loss) | true |
