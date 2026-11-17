
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 422.6 | 0.0571126 | 234.258ms | 905 | 40 | 54.4205 | 2042.3 | 0.0538318 | 5.78948 | 1(Win) | true |
| simdjson (ondemand) | 204.135 | 0.0419686 | 414.014ms | 905 | 80 | 251.885 | 4227.96 | 0.00147828 | 12.0497 | 2(Loss) | true |
