
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4727.56 | 0.0766474 | 87.5974ms | 3873 | 80 | 28.6884 | 781.288 | 0.0176023 | 0.505651 | 1(Win) | true |
| Glaze | 2378.3 | 0.0878372 | 164.241ms | 3873 | 30 | 55.8264 | 1553.03 | 0.0945281 | 1.02307 | 2(Loss) | true |
