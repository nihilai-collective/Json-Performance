
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2999.64 | 0.107137 | 5143.43ms | 631514 | 320 | 1.48066e+07 | 200777 | 0.180844 | 1.01313 | 1(Win) | true |
| Glaze | 2397.5 | 0.0536554 | 6441.99ms | 631514 | 160 | 2.90666e+06 | 251202 | 0.319986 | 1.26757 | 2(Loss) | true |
