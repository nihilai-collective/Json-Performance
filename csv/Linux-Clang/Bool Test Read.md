
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1910.73 | 0.155779 | 46.3337ms | 905 | 40 | 19.8051 | 451.7 | 0.00737898 | 1.22083 | 1(Win) | true |
| Glaze | 1475.66 | 0.13443 | 63.247ms | 905 | 40 | 24.7276 | 584.875 | 0.0555366 | 1.60298 | 2(Loss) | true |
| simdjson (ondemand) | 449.603 | 0.0357979 | 191.841ms | 905 | 80 | 37.7783 | 1919.64 | 0.309644 | 5.42938 | 3(Loss) | true |
