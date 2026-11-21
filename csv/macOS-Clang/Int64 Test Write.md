
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2973.91 | 0.406605 | 127.903ms | 3862 | 1280 | 32458.2 | 1238.47 | 0.357528 | 1(Win) | true |
| Glaze | 524.519 | 0.14072 | 733.934ms | 3862 | 1280 | 124976 | 7021.84 | 0.0051071 | 2(Loss) | true |
