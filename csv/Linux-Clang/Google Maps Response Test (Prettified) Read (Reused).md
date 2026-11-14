
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3675.07 | 0.124735 | 1455.3ms | 25388 | 640 | 43220.2 | 6588.15 | 0.0248377 | 1.38319 | 6.73732 | 1.04171 | 0.0029744 | 8.12392e-06 | 1.7848e-06 | 1(Win) | true |
| Jsonifier | 3096.74 | 0.0525838 | 1566.96ms | 25388 | 4890 | 82653.7 | 7818.52 | 0.214925 | 1.64119 | 7.443 | 1.55073 | 0.00448818 | 1.437e-05 | 5.09878e-06 | 2(Loss) | true |
| Glaze | 2580.51 | 0.0642629 | 1735.28ms | 25388 | 2560 | 93069.3 | 9382.59 | 0.285834 | 1.97206 | 9.10391 | 1.77568 | 0.0046068 | 2.07098e-05 | 9.73947e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2299.69 | 0.0685986 | 1852.36ms | 25388 | 2560 | 133534 | 10528.3 | 0.049478 | 2.20542 | 9.75788 | 1.5232 | 0.0031925 | 2.29101e-05 | 9.00093e-06 | 4(Loss) | true |
