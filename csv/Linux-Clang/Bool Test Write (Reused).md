
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4132.95 | 0.0539531 | 28.4301ms | 905 | 1280 | 16.2488 | 208.828 | 0.0981134 | 0.526376 | 1(Win) | true |
| Glaze | 965.355 | 0.16366 | 100.207ms | 905 | 40 | 85.6385 | 894.05 | 0.0839584 | 2.48923 | 2(Loss) | true |
