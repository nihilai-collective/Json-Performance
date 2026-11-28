
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1792.18 | 0.131532 | 228.568ms | 4215 | 160 | 1392.57 | 2242.94 | 0.159085 | 1.36547 | 1(Win) | true |
| simdjson (reflection) | 1589.1 | 0.125151 | 263.697ms | 4215 | 80 | 801.768 | 2529.56 | 0.394259 | 1.54192 | 2(Loss) | true |
| Glaze | 983.942 | 0.148557 | 414.14ms | 4215 | 4890 | 180115 | 4085.34 | 0.427005 | 2.50025 | 3(Loss) | true |
