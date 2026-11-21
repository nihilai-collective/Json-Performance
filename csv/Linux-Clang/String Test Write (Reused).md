
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13367.3 | 0.151845 | 83.4339ms | 9578 | 30 | 32.2989 | 683.333 | 0.204459 | 0.178329 | 1(Win) | true |
| Glaze | 5468.65 | 0.137483 | 178.295ms | 9578 | 40 | 210.933 | 1670.3 | 0.0678982 | 0.445714 | 2(Loss) | true |
