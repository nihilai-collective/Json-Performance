
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2430.19 | 0.0787767 | 38.7343ms | 905 | 320 | 25.0473 | 355.147 | 0.108113 | 0.945566 | 1(Win) | true |
| Jsonifier | 2361.19 | 0.21461 | 40.2017ms | 905 | 40 | 24.6147 | 365.525 | 0.2751 | 0.973204 | 2(Loss) | true |
| Jsonifier (two-stage) | 455.641 | 0.0487153 | 195.225ms | 905 | 30 | 25.5448 | 1894.2 | 0.0175945 | 5.35974 | 3(Loss) | true |
| simdjson (ondemand) | 210.775 | 0.0522167 | 410.793ms | 905 | 30 | 137.151 | 4094.77 | 0.0975903 | 11.6726 | 4(Loss) | true |
