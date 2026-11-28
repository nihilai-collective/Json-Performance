
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1958.55 | 0.0436912 | 248.672ms | 4215 | 160 | 128.657 | 2052.4 | 0.535152 | 1.24755 | 1(Win) | true |
| Glaze | 1271.48 | 0.283669 | 358.691ms | 4215 | 30 | 2412.81 | 3161.47 | 0.274434 | 1.9311 | 2(Loss) | true |
| simdjson (ondemand) | 939.218 | 0.0807784 | 461.551ms | 4215 | 80 | 956.187 | 4279.88 | 0.237133 | 2.61917 | 3(Loss) | true |
