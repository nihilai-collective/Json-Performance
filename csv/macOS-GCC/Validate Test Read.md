
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2312.28 | 0.156413 | 6787.16ms | 631514 | 640 | 1.06221e+08 | 260461 | 0.160227 | 1(Win) | true |
| Glaze | 1859.81 | 0.482707 | 8084.41ms | 631514 | 40 | 9.77359e+07 | 323827 | 0.655776 | 2(Loss) | true |
