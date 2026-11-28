
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1581.88 | 1.83136 | 56.2742ms | 905 | 2560 | 255585 | 545.6 | 0.619308 | 1(Win) | true |
| simdjson (reflection) | 201.861 | 0.914581 | 416.708ms | 905 | 640 | 978630 | 4275.6 | 2.71958 | 2(Loss) | true |
| Glaze | 114.345 | 0.220895 | 746.766ms | 905 | 4890 | 1.3594e+06 | 7548.02 | 0.416628 | 3(Loss) | true |
