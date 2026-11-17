
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1387.35 | 0.0417026 | 977.921ms | 3862 | 4890 | 5993.64 | 2654.77 | 0.136763 | 3.75899 | 17.6567 | 1.90471 | 0.000266823 | 4.31555e-05 | 4.50088e-06 | 1(Win) | true |
| simdjson (ondemand) | 759.292 | 0.0249562 | 1201.23ms | 3862 | 4890 | 7165.93 | 4850.69 | 0.0470601 | 6.8266 | 31.5601 | 3.45236 | 0.00182461 | 3.92901e-05 | 4.87154e-06 | 2(Loss) | true |
