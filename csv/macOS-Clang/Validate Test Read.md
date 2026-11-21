
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2268.91 | 0.437947 | 6517.63ms | 631514 | 320 | 4.32438e+08 | 265439 | 0.264291 | 1(Win) | true |
| Glaze | 1997.75 | 0.134615 | 7762.33ms | 631514 | 80 | 1.31753e+07 | 301469 | 0.158013 | 2(Loss) | true |
