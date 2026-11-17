
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16400.5 | 0.377265 | 1206.55ms | 78778 | 1280 | 382296 | 4580.87 | 0.0787349 | 0.309116 | 1.08476 | 0.182069 | 2.60423e-05 | 1.22179e-05 | 6.56513e-06 | 1(Win) | true |
| Glaze | 5126.98 | 0.120229 | 2214.21ms | 78778 | 4890 | 1.5178e+06 | 14653.6 | 0.300373 | 0.984571 | 2.95713 | 0.474155 | 0.000366825 | 2.78617e-05 | 1.51185e-05 | 2(Loss) | true |
