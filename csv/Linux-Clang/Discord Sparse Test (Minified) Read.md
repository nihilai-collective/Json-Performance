
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.72 | 0.0200617 | 2990.8ms | 56369 | 2560 | 51964.7 | 22457.8 | 0.3049 | 2.15189 | 9.92209 | 1.77376 | 0.00350093 | 2.52937e-05 | 1.61325e-05 | 1(Win) | true |
| simdjson (ondemand) | 1910.86 | 0.0442264 | 3536.16ms | 56369 | 1280 | 198152 | 28132.8 | 0.0761647 | 2.67458 | 10.4523 | 1.7053 | 0.010659 | 8.9117e-06 | 3.58963e-06 | 2(Loss) | true |
