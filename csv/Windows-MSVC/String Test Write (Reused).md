
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7510.21 | 0.240546 | 134.302ms | 9578 | 160 | 1369.5 | 1216.25 | 0.61287 | 0.322361 | 1(Win) | true |
| Glaze | 4154.31 | 0.0988825 | 300.17ms | 9578 | 80 | 378.165 | 2198.75 | 0.170843 | 0.587935 | 2(Loss) | true |
