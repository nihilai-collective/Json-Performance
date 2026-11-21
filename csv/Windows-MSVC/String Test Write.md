
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1271.3 | 0.265624 | 761.731ms | 9578 | 80 | 29139.2 | 7185 | 0.0347826 | 1.94062 | 1(Win) | true |
| Glaze | 650.785 | 1.11456 | 1420.09ms | 9578 | 4890 | 1.19671e+08 | 14035.8 | 0.28599 | 3.79644 | 2(Loss) | true |
