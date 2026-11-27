
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4034.27 | 0.0481623 | 7669.72ms | 631514 | 1280 | 6.61702e+06 | 149286 | 0.135967 | 0.613588 | 1(Win) | true |
| Glaze | 2640.14 | 0.110455 | 5859.79ms | 631514 | 1280 | 8.12631e+07 | 228116 | 0.0432333 | 0.937653 | 2(Loss) | true |
