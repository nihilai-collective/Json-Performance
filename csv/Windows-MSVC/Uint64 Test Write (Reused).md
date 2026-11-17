
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4484.29 | 0.14747 | 98.0336ms | 3873 | 2560 | 3777.06 | 823.672 | 0.160985 | 0.657493 | 1(Win) | true |
| Glaze | 1705.43 | 0.089624 | 244.671ms | 3873 | 2560 | 9645.34 | 2165.78 | 0.0866489 | 1.76291 | 2(Loss) | true |
