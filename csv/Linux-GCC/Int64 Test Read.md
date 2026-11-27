
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2719.31 | 0.188712 | 750.656ms | 1313 | 40 | 30.2045 | 460.475 | 0.0742538 | 2.06582 | 9.85225 | 2.49276 | 0.000761615 | 1.90404e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 1218.11 | 0.139097 | 813.223ms | 1313 | 640 | 1308.48 | 1027.96 | 0.229284 | 4.42936 | 24.92 | 5.68926 | 0.000982959 | 0.000174933 | 3.33206e-05 | 2(Loss) | true |
