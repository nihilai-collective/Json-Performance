
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 622.075 | 0.026144 | 1442.11ms | 4669 | 2560 | 8964.92 | 7157.83 | 0.0141637 | 8.33004 | 37.8929 | 7.49754 | 0.00892447 | 4.14134e-05 | 6.35843e-06 | 1(Win) | true |
| simdjson (ondemand) | 247.29 | 0.160683 | 2536.5ms | 4669 | 80 | 66967.7 | 18006 | 0.0952248 | 20.8727 | 103.945 | 18.7781 | 0.0348736 | 4.5513e-05 | 0 | 2(Loss) | true |
