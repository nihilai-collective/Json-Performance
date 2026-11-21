
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4510.06 | 0.0286626 | 90.709ms | 3873 | 640 | 35.2647 | 818.964 | 0.0471473 | 0.531887 | 1(Win) | true |
| Glaze | 2592.41 | 0.089459 | 153.437ms | 3873 | 30 | 48.7368 | 1424.77 | 0.00233951 | 0.936905 | 2(Loss) | true |
