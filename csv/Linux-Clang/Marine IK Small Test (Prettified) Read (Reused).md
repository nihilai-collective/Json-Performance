
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2341.46 | 0.0536979 | 1573.44ms | 18245 | 640 | 10190.8 | 7431.18 | 0.056719 | 2.21043 | 8.94541 | 1.7345 | 0.00244648 | 7.70759e-06 | 5.13839e-07 | 1(Win) | true |
| simdjson (ondemand) | 2208.1 | 0.0353073 | 1607.38ms | 18245 | 2560 | 19816.3 | 7879.99 | 0.0835088 | 2.32069 | 9.63015 | 1.57084 | 0.00271521 | 1.89264e-05 | 7.32221e-06 | 2(Loss) | true |
