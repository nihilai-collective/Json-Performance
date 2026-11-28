
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1768.8 | 0.0618367 | 74.1177ms | 1313 | 160 | 30.661 | 707.925 | 0.0494647 | 1.34903 | 1(Win) | true |
| simdjson (reflection) | 1028.34 | 0.0247817 | 126.261ms | 1313 | 320 | 29.1386 | 1217.67 | 0.125139 | 2.35736 | 2(Loss) | true |
| Glaze | 934.412 | 0.0908629 | 137.318ms | 1313 | 30 | 44.4782 | 1340.07 | 0.151964 | 2.60244 | 3(Loss) | true |
| simdjson (ondemand) | 355.025 | 0.0305489 | 357.765ms | 1313 | 30 | 34.8276 | 3527 | 0.0755501 | 6.92138 | 4(Loss) | true |
