
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 356.784 | 0.017577 | 548.252ms | 1997 | 80 | 70.4247 | 5337.93 | 0.0445127 | 6.9045 | 1(Win) | true |
| Glaze | 272.999 | 0.0644198 | 634.995ms | 1798 | 40 | 654.872 | 6281 | 0.018578 | 9.02977 | 2(Loss) | true |
