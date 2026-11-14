
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1308.64 | 0.0466254 | 841.467ms | 1691 | 1280 | 422.572 | 1232.32 | 0.0157833 | 4.06547 | 14.7363 | 2.89769 | 0.000593676 | 0.000103027 | 1.15501e-05 | 1(Win) | true |
| simdjson (ondemand) | 1191.53 | 0.0396911 | 853.252ms | 1691 | 4890 | 1411.16 | 1353.44 | 0.0879412 | 4.45055 | 16.8102 | 2.90893 | 0.000633088 | 9.56586e-05 | 5.68389e-06 | 2(Loss) | true |
