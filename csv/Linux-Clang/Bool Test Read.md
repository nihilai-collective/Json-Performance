
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 295.733 | 0.420916 | 298.229ms | 905 | 2560 | 386304 | 2918.43 | 0.657688 | 8.29114 | 1(Win) | true |
| simdjson (ondemand) | 249.855 | 0.0428938 | 351.05ms | 905 | 80 | 175.63 | 3454.3 | 0.118552 | 9.82783 | 2(Loss) | true |
