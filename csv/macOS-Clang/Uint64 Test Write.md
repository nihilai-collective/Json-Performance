
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2887.56 | 0.543713 | 139.342ms | 3873 | 30 | 1451.09 | 1279.13 | 0.104346 | 1(Win) | true |
| Glaze | 502.125 | 0.478883 | 730.657ms | 3873 | 1280 | 1.58833e+06 | 7355.9 | 0.326396 | 2(Loss) | true |
