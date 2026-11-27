
----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4959.12 | 0.07975 | 6106.1ms | 277673 | 640 | 1.16064e+06 | 53398.5 | 0.0217714 | 1.03218 | 4.20971 | 0.692768 | 0.00463279 | 3.46631e-06 | 2.29587e-06 | 1(Win) | true |
| simdjson (ondemand) | 4199.17 | 0.0605366 | 7051.27ms | 277673 | 1280 | 1.86546e+06 | 63062.3 | 0.0624041 | 1.20512 | 4.65244 | 0.757382 | 0.00309128 | 2.14112e-06 | 1.02976e-06 | 2(Loss) | true |
