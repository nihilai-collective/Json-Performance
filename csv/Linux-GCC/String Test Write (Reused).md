
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5364.03 | 0.0941036 | 84.8649ms | 4215 | 80 | 39.7847 | 749.388 | 0.20224 | 0.445549 | 1(Win) | true |
| simdjson (reflection) | 3851.06 | 0.0870654 | 113.476ms | 4215 | 40 | 33.0359 | 1043.8 | 0.0543183 | 0.625629 | 2(Loss) | true |
| Glaze | 2741.66 | 0.084145 | 163.26ms | 4215 | 30 | 45.6609 | 1466.17 | 0.0227299 | 0.885987 | 3(Loss) | true |
