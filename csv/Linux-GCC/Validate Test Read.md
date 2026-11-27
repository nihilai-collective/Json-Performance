
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2682.43 | 0.0973561 | 5924.3ms | 631514 | 640 | 3.05785e+07 | 224520 | 0.195508 | 1.89721 | 8.33046 | 1.35779 | 0.010128 | 3.07149e-05 | 2.31908e-05 | 1(Win) | true |
| Glaze | 2162.92 | 0.0862106 | 7310.15ms | 631514 | 640 | 3.68796e+07 | 278447 | 0.0712224 | 2.34368 | 9.80794 | 1.64391 | 0.00988455 | 2.27479e-05 | 2.12386e-05 | 2(Loss) | true |
