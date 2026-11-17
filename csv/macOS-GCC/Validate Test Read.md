
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2095.86 | 0.286172 | 7682.48ms | 631514 | 320 | 2.16393e+08 | 287356 | 0.369124 | 1(Win) | true |
| Glaze | 1636 | 0.566697 | 8696.64ms | 631514 | 160 | 6.96342e+08 | 368130 | 0.329226 | 2(Loss) | true |
