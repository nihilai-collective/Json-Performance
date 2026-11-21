
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 435.063 | 0.128347 | 446.193ms | 1997 | 80 | 2525.32 | 4377.5 | 0.114351 | 5.64273 | 1(Win) | true |
| Glaze | 106.17 | 0.92039 | 1656.53ms | 1798 | 4890 | 1.08051e+08 | 16150.6 | 0.0246201 | 23.2719 | 2(Loss) | true |
