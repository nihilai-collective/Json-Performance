
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5111.81 | 0.0275484 | 81.1699ms | 3873 | 640 | 25.3582 | 722.558 | 0.0481995 | 0.467192 | 1(Win) | true |
| Glaze | 2657.76 | 0.0751074 | 148.992ms | 3873 | 30 | 32.6851 | 1389.73 | 0.050344 | 0.91297 | 2(Loss) | true |
