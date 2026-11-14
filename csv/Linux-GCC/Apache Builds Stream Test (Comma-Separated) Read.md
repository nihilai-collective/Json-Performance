
----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1956.18 | 0.138139 | 8244.27ms | 4211999 | 30 | 2.41387e+08 | 2.05343e+06 | 0.0557979 | 2.5981 | 12.1252 | 2.20728 | 0.0122777 | 0.0684452 | 0.000912069 | 1(Win) | true |
| simdjson (ondemand) | 1267.72 | 0.111591 | 5660.55ms | 4211999 | 80 | 1.00019e+09 | 3.16858e+06 | 0.107917 | 4.02203 | 15.072 | 3.10875 | 0.0124804 | 0.0674668 | 0.00366818 | 2(Loss) | true |
