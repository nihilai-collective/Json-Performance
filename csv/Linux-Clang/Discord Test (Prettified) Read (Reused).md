
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4225.32 | 0.0669764 | 3012.18ms | 83958 | 4890 | 787693 | 18949.7 | 0.285085 | 1.20057 | 6.09968 | 1.19773 | 0.00136256 | 1.64022e-05 | 8.4739e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3173.05 | 0.0733062 | 3634.38ms | 83958 | 2560 | 875972 | 25233.9 | 0.136818 | 1.59642 | 7.93814 | 1.31936 | 0.00201714 | 1.63633e-05 | 1.0059e-05 | 2(Loss) | true |
| Glaze | 2882.39 | 0.0635016 | 3870.64ms | 83958 | 4890 | 1.52159e+06 | 27778.5 | 0.0387039 | 1.7617 | 8.98655 | 1.80239 | 0.00357825 | 2.37459e-05 | 1.55984e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1599.46 | 0.196068 | 6137.8ms | 83958 | 320 | 3.08276e+06 | 50059.7 | 0.127466 | 3.15796 | 13.8885 | 2.08586 | 0.00645408 | 2.25187e-05 | 1.35112e-05 | 4(Loss) | true |
