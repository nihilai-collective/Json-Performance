
----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1098.66 | 3.35669 | 5606.85ms | 4203059 | 40 | 5.99916e+11 | 3.64841e+06 | 0.478083 | 2.25346 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1070.14 | 0.173416 | 6004.41ms | 4203059 | 30 | 1.26577e+09 | 3.74565e+06 | 1.44134 | 2.31351 | 1(Tie) | true |
