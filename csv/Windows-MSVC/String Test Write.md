
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 489.55 | 0.190128 | 846.996ms | 4215 | 2560 | 623925 | 8211.09 | 0.227916 | 5.03915 | 1(Win) | true |
| Glaze | 402.445 | 0.273161 | 1025.03ms | 4215 | 1280 | 952857 | 9988.28 | 0.462458 | 6.13527 | 2(Loss) | true |
