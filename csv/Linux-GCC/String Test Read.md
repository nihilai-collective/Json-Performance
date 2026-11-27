
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2357.82 | 0.053527 | 174.219ms | 4215 | 40 | 33.3103 | 1704.85 | 0.0224798 | 1.03289 | 1(Win) | true |
| simdjson (stage-1) | 2238.16 | 0.0619313 | 183.928ms | 4215 | 40 | 49.4872 | 1796 | 0.0222668 | 1.09071 | 2(Loss) | true |
