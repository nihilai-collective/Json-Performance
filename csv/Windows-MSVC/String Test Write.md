
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1305.32 | 0.27945 | 720.999ms | 9578 | 1280 | 489479 | 6997.73 | 0.124078 | 1.88917 | 1(Win) | true |
| Glaze | 557.607 | 0.254236 | 1148.69ms | 9578 | 80 | 138758 | 16381.2 | 0.205605 | 4.43218 | 2(Loss) | true |
