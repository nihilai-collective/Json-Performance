
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1440.62 | 0.0936643 | 1362.26ms | 9578 | 1280 | 45144.8 | 6340.52 | 0.00347456 | 3.54214 | 17.6752 | 3.00209 | 0.00303552 | 4.09467e-05 | 2.15337e-05 | 1(Win) | true |
| Jsonifier (generic) | 1329.34 | 0.188552 | 1414.47ms | 9578 | 80 | 13428.6 | 6871.31 | 0.289536 | 3.89335 | 19.1543 | 3.34673 | 0.00353936 | 1.95761e-05 | 7.83044e-06 | 2(Loss) | true |
