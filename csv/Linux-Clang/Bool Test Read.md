
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 651.255 | 0.0782476 | 139.589ms | 905 | 40 | 43.0128 | 1325.25 | 0.296418 | 3.72323 | 1(Win) | true |
| simdjson (ondemand) | 467.494 | 0.0477408 | 187.278ms | 905 | 80 | 62.1462 | 1846.17 | 0.518644 | 5.22314 | 2(Loss) | true |
