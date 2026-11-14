
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2353.8 | 0.112919 | 10062.2ms | 7351818 | 40 | 4.52529e+08 | 2.97869e+06 | 0.162462 | 2.15271 | 9.29634 | 1.68823 | 0.0100872 | 0.0536666 | 0.00301817 | 1(Win) | true |
| simdjson (ondemand) | 2251.38 | 0.0986035 | 5108.75ms | 7351818 | 30 | 2.82877e+08 | 3.1142e+06 | 0.834218 | 2.24744 | 9.45416 | 1.45213 | 0.0108794 | 0.0535217 | 0.0031925 | 2(Loss) | true |
