
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5154.16 | 0.240609 | 816.494ms | 3862 | 640 | 1891.96 | 714.586 | 0.0391551 | 1.05768 | 5.36665 | 0.628949 | 0.000270666 | 3.07483e-05 | 1.21375e-06 | 1(Win) | true |
| Glaze | 2208.23 | 0.0539204 | 918.663ms | 3862 | 4890 | 3955.06 | 1667.9 | 0.229787 | 2.38372 | 8.65251 | 1.04868 | 0.00528695 | 9.13415e-05 | 4.75505e-05 | 2(Loss) | true |
