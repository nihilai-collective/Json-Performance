
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2944.97 | 0.160869 | 129.13ms | 3873 | 40 | 162.831 | 1254.2 | 0.229089 | 1(Win) | true |
| Glaze | 557.252 | 0.0726954 | 674.325ms | 3873 | 40 | 928.677 | 6628.2 | 0.0346882 | 2(Loss) | true |
