
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1031.26 | 0.06399 | 87.1587ms | 905 | 1280 | 367.109 | 836.913 | 0.154825 | 1(Win) | true |
| Glaze | 131.229 | 0.243389 | 675.523ms | 905 | 4890 | 1.25299e+06 | 6576.88 | 0.5699 | 2(Loss) | true |
