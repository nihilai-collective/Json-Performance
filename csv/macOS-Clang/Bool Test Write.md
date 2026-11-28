
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1032.3 | 0.0590483 | 94.4496ms | 905 | 640 | 155.984 | 836.07 | 0.0924232 | 1(Win) | true |
| Glaze | 123.49 | 0.182949 | 711.539ms | 905 | 4890 | 799472 | 6989.04 | 0.28058 | 2(Loss) | true |
