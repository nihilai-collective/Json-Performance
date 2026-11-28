
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3892.67 | 0.0436747 | 30.0058ms | 905 | 1280 | 12.0025 | 221.718 | 0.113236 | 0.557611 | 1(Win) | true |
| Glaze | 938.189 | 0.0677404 | 100.28ms | 905 | 160 | 62.1344 | 919.938 | 0.0475802 | 2.56112 | 2(Loss) | true |
