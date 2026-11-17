
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2258.67 | 1.29138 | 6843.4ms | 631514 | 30 | 3.55704e+08 | 266643 | 0.463508 | 1(Win) | true |
| Glaze | 1796.28 | 0.288512 | 8492.39ms | 631514 | 640 | 5.98858e+08 | 335280 | 0.511968 | 2(Loss) | true |
