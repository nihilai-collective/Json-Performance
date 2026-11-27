
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10348.9 | 0.0166304 | 5042.43ms | 466906 | 4890 | 250374 | 43026.6 | 0.0829271 | 0.496587 | 1.97404 | 0.0757841 | 3.12206e-05 | 0.000251048 | 7.00342e-06 | 1(Win) | true |
| simdjson (ondemand) | 9319.99 | 0.0222453 | 5523.7ms | 466906 | 2560 | 289166 | 47776.5 | 0.0822562 | 0.552007 | 2.07166 | 0.0435849 | 7.97688e-05 | 0.000750839 | 7.15147e-06 | 2(Loss) | true |
| Glaze | 2533.27 | 0.0982041 | 9397.71ms | 466906 | 40 | 1.19184e+06 | 175772 | 0.0154011 | 2.0315 | 8.75451 | 1.96144 | 0.0025549 | 0.00101584 | 3.06271e-05 | 3(Loss) | true |
