
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4356.14 | 0.408118 | 92.9002ms | 3862 | 4890 | 58224.1 | 845.494 | 0.118764 | 0.550049 | 1(Win) | true |
| Glaze | 2336.64 | 0.191337 | 168.359ms | 3862 | 4890 | 44478.5 | 1576.23 | 0.634441 | 1.03916 | 2(Loss) | true |
