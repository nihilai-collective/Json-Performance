
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3026.48 | 0.117834 | 125.866ms | 3862 | 160 | 329.011 | 1216.96 | 0.0251716 | 1(Win) | true |
| Glaze | 550.828 | 0.0683117 | 680.232ms | 3862 | 80 | 1669.06 | 6686.46 | 0.0626658 | 2(Loss) | true |
