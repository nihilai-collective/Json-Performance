
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12707.3 | 0.095648 | 82.8944ms | 9578 | 80 | 37.8171 | 718.825 | 0.0696064 | 0.187431 | 1(Win) | true |
| Glaze | 4994.69 | 0.126236 | 194.107ms | 9578 | 30 | 159.89 | 1828.8 | 0.109481 | 0.488345 | 2(Loss) | true |
