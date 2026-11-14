
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3536.49 | 0.199451 | 8974.7ms | 631514 | 160 | 1.84593e+07 | 170299 | 0.233286 | 1.40058 | 7.07843 | 1.22888 | 0.00445103 | 2.30597e-06 | 7.52161e-07 | 1(Win) | true |
| Glaze | 2634.85 | 0.135335 | 6040.28ms | 631514 | 80 | 7.65538e+06 | 228574 | 0.0112886 | 1.91768 | 8.44884 | 1.51664 | 0.00304633 | 2.09813e-06 | 9.50098e-07 | 2(Loss) | true |
