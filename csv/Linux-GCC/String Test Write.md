
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1683.96 | 0.223691 | 246.407ms | 4215 | 40 | 1140.48 | 2387.07 | 0.200332 | 1.45295 | 1(Win) | true |
| simdjson (reflection) | 1497.09 | 0.185183 | 276.809ms | 4215 | 30 | 741.689 | 2685.03 | 0.174739 | 1.63646 | 2(Loss) | true |
| Glaze | 919.973 | 0.220612 | 441.059ms | 4215 | 4890 | 454374 | 4369.41 | 0.448564 | 2.67415 | 3(Loss) | true |
