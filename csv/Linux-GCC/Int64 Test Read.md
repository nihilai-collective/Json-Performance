
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1769.78 | 0.2519 | 74.1422ms | 1313 | 160 | 508.238 | 707.531 | 0.268699 | 1.35047 | 1(Win) | true |
| simdjson (reflection) | 1037.1 | 0.0560904 | 130.664ms | 1313 | 160 | 73.3805 | 1207.38 | 0.489363 | 2.33652 | 2(Loss) | true |
| Glaze | 928.174 | 0.39052 | 139.232ms | 1313 | 2560 | 71055.5 | 1349.07 | 0.0263422 | 2.6155 | 3(Loss) | true |
| simdjson (ondemand) | 354.186 | 0.0148973 | 359.274ms | 1313 | 160 | 44.3817 | 3535.36 | 0.0213865 | 6.93988 | 4(Loss) | true |
