
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2345 | 0.0464604 | 3040.31ms | 56369 | 320 | 36300.4 | 22924.4 | 0.0916034 | 2.19904 | 9.90158 | 1.76729 | 0.00380822 | 3.65893e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2031.89 | 0.0822825 | 3390.28ms | 56369 | 320 | 151651 | 26457 | 0.0902419 | 2.53807 | 10.4997 | 1.7176 | 0.00690883 | 1.31389e-05 | 7.15154e-06 | 2(Loss) | true |
