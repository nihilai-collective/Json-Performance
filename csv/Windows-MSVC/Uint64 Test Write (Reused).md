
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2983.86 | 0.308933 | 131.963ms | 3873 | 2560 | 37437.4 | 1237.85 | 0.702301 | 0.811755 | 1(Win) | true |
| Glaze | 1117.01 | 0.140082 | 344.392ms | 3873 | 30 | 643.678 | 3306.67 | 0.100705 | 2.19564 | 2(Loss) | true |
