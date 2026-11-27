
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2662.63 | 0.041037 | 4091.73ms | 83958 | 2560 | 389848 | 30071.3 | 0.0525708 | 1.90777 | 8.77832 | 1.60068 | 0.00324188 | 2.18859e-05 | 1.02637e-05 | 1(Win) | true |
| simdjson (ondemand) | 2114.38 | 0.0629723 | 4858.17ms | 83958 | 320 | 181973 | 37868.6 | 0.0161935 | 2.39558 | 9.65718 | 1.60044 | 0.0085701 | 6.9231e-06 | 2.90324e-06 | 2(Loss) | true |
