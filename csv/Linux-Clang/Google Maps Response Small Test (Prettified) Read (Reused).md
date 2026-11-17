
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2603.45 | 0.0374974 | 1091.18ms | 9378 | 2560 | 4247.82 | 3435.27 | 0.0950848 | 2.00503 | 8.63702 | 1.53679 | 0.00159386 | 1.76194e-05 | 2.41589e-06 | 1(Win) | true |
| simdjson (ondemand) | 2291.42 | 0.0344015 | 1149.23ms | 9378 | 2560 | 4615.37 | 3903.07 | 0.176304 | 2.24491 | 9.60002 | 1.55257 | 0.00176306 | 1.99103e-05 | 4.20699e-06 | 2(Loss) | true |
