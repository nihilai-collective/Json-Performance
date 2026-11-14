
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2436.54 | 0.13552 | 9910.96ms | 7351818 | 40 | 6.08283e+08 | 2.87753e+06 | 0.395826 | 1.01609 | 1(Win) | true |
| simdjson (ondemand) | 2394.23 | 0.224927 | 9588.45ms | 7351818 | 30 | 1.30156e+09 | 2.92839e+06 | 0.395412 | 1.03405 | 2(Loss) | true |
