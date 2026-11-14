
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1611.71 | 0.0751951 | 1299.71ms | 9378 | 320 | 5571.55 | 5549.12 | 0.00106998 | 3.21854 | 14.2305 | 2.76104 | 0.00596976 | 2.39923e-05 | 5.99808e-06 | 1(Win) | true |
| simdjson (ondemand) | 1523.3 | 0.0251084 | 1342.57ms | 9378 | 2560 | 5563.26 | 5871.18 | 0.0550055 | 3.40347 | 15.3414 | 2.70729 | 0.00468142 | 1.89939e-05 | 2.45755e-06 | 2(Loss) | true |
