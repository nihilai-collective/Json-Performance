
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1273.19 | 0.344303 | 720.004ms | 9578 | 320 | 195252 | 7174.35 | 1.05461 | 1(Win) | true |
| Glaze | 1028.16 | 0.315569 | 906.083ms | 9578 | 1280 | 1.00607e+06 | 8884.12 | 0.113285 | 2(Loss) | true |
