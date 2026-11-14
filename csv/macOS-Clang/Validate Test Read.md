
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2528.84 | 0.305022 | 6056.43ms | 631514 | 160 | 8.44313e+07 | 238156 | 0.366374 | 1(Win) | true |
| Glaze | 1988.45 | 0.114903 | 7729.56ms | 631514 | 1280 | 1.5503e+08 | 302879 | 0.298522 | 2(Loss) | true |
