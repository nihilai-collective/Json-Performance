
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2205.64 | 0.0684776 | 9893.43ms | 7351818 | 160 | 7.5812e+08 | 3.17878e+06 | 0.105734 | 2.28272 | 9.65712 | 1.8855 | 0.0102851 | 0.0588955 | 0.00661619 | 1(Win) | true |
| simdjson (ondemand) | 2094.06 | 0.206371 | 5005.09ms | 7351818 | 30 | 1.43229e+09 | 3.34816e+06 | 0.440604 | 2.41444 | 10.2023 | 1.62706 | 0.0109843 | 0.0588178 | 0.00534768 | 2(Loss) | true |
