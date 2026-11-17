
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20213.2 | 0.237575 | 3003.19ms | 631514 | 640 | 3.20683e+06 | 29795.3 | 0.0794853 | 0.122374 | 1(Win) | true |
| simdjson (stage-1) | 16236.3 | 0.55319 | 3719.97ms | 631514 | 160 | 6.73692e+06 | 37093.4 | 0.118625 | 0.152372 | 2(Loss) | true |
