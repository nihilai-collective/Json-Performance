
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4486.02 | 0.08913 | 6994.05ms | 10548466 | 80 | 3.19591e+08 | 2.24248e+06 | 0.155885 | 1.14226 | 4.00436 | 0.654211 | 0.0115636 | 0.017241 | 0.000326987 | 1(Win) | true |
| simdjson (ondemand) | 3853.87 | 0.0635548 | 8202.46ms | 10548466 | 160 | 4.40354e+08 | 2.61031e+06 | 0.705752 | 1.33157 | 4.49725 | 0.722092 | 0.0102688 | 0.0174891 | 6.11671e-05 | 2(Loss) | true |
