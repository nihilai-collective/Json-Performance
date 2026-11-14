
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1390.34 | 0.0300254 | 1376.08ms | 9578 | 4890 | 19028.1 | 6569.82 | 0.0245309 | 3.72344 | 17.7196 | 3.34172 | 0.00222079 | 2.47243e-05 | 9.71466e-06 | 1(Win) | true |
| simdjson (ondemand) | 1358.92 | 0.0497313 | 1398.9ms | 9578 | 1280 | 14303.2 | 6721.74 | 0.0982038 | 3.79251 | 19.237 | 2.98089 | 0.00372819 | 1.68844e-05 | 1.71291e-06 | 2(Loss) | true |
