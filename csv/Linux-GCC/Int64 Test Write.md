
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 385.709 | 0.0449487 | 325.316ms | 1313 | 40 | 85.1737 | 3246.43 | 0.117961 | 6.36915 | 1(Win) | true |
| simdjson (reflection) | 368.561 | 0.0544879 | 334.318ms | 1313 | 30 | 102.809 | 3397.47 | 0.205612 | 6.66527 | 2(Loss) | true |
| Glaze | 323.905 | 0.0497915 | 388.921ms | 1313 | 30 | 111.154 | 3865.87 | 0.0585985 | 7.59327 | 3(Loss) | true |
