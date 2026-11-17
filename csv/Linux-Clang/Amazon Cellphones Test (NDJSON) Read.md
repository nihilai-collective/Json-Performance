
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4731.19 | 0.10035 | 6349.7ms | 277673 | 640 | 2.01902e+06 | 55971 | 0.303977 | 1.0786 | 4.29122 | 0.683817 | 0.0048865 | 2.17207e-06 | 8.77831e-07 | 1(Win) | true |
| simdjson (ondemand) | 3763.67 | 0.0832769 | 7773.14ms | 277673 | 640 | 2.19723e+06 | 70359.5 | 0.0410801 | 1.35833 | 4.69215 | 0.770977 | 0.00471658 | 8.94712e-06 | 6.41492e-06 | 2(Loss) | true |
