
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9730.08 | 0.375077 | 784.384ms | 4857 | 2560 | 8161.77 | 476.049 | 0.158618 | 0.563973 | 1.69014 | 0.291744 | 0.000260175 | 2.60578e-05 | 5.30806e-06 | 1(Win) | true |
| Glaze | 2789.35 | 0.134568 | 903.231ms | 4857 | 4890 | 24418.6 | 1660.6 | 0.0779233 | 1.85804 | 4.17954 | 0.637225 | 0.00021313 | 3.25043e-05 | 4.42092e-06 | 2(Loss) | true |
