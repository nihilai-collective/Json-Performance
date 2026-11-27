
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.75 | 0.228471 | 87.2548ms | 905 | 2560 | 9497.44 | 843.049 | 0.0182129 | 1(Win) | true |
| Glaze | 131.48 | 0.100674 | 663.245ms | 905 | 2560 | 111804 | 6564.32 | 0.00524882 | 2(Loss) | true |
