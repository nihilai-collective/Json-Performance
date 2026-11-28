
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 335.604 | 0.381653 | 587.625ms | 1997 | 640 | 300205 | 5674.8 | 0.190678 | 1(Win) | true |
| simdjson (reflection) | 324.776 | 0.317447 | 634.45ms | 1997 | 640 | 221774 | 5864 | 0.163979 | 2(Loss) | true |
| Glaze | 205.069 | 0.492232 | 828.675ms | 1798 | 640 | 1.08417e+06 | 8361.6 | 0.124224 | 3(Loss) | true |
