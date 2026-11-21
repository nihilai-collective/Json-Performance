
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4189 | 0.049758 | 7531.01ms | 631514 | 1280 | 6.55062e+06 | 143772 | 0.127334 | 0.590911 | 1(Win) | true |
| Glaze | 2652.96 | 0.0782327 | 5844.05ms | 631514 | 320 | 1.00933e+07 | 227014 | 0.0906989 | 0.933123 | 2(Loss) | true |
