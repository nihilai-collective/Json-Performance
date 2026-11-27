
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 489.019 | 0.236214 | 832.009ms | 4215 | 30 | 11310.3 | 8220 | 0.323363 | 6.2022 | 1(Win) | true |
| simdjson (ondemand) | 482.182 | 0.0841734 | 848.092ms | 4215 | 2560 | 126056 | 8336.56 | 0.563771 | 6.28628 | 2(Loss) | true |
