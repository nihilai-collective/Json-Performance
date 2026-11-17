
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 919.133 | 1.21712 | 5651.74ms | 7351818 | 40 | 3.44795e+11 | 7.6281e+06 | 0.0731166 | 2.69364 | 1(Win) | true |
| simdjson (ondemand) | 832.662 | 0.840379 | 6110.77ms | 7351818 | 40 | 2.00291e+11 | 8.42027e+06 | 0.0894972 | 2.97337 | 2(Loss) | true |
