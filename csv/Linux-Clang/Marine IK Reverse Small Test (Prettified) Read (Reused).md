
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3052.54 | 0.174599 | 664.704ms | 18245 | 2560 | 253564 | 5700.11 | 0.239354 | 0.806841 | 1(Win) | true |
| Jsonifier | 2354.18 | 0.209012 | 837.91ms | 18245 | 2560 | 610933 | 7391.03 | 0.189142 | 1.04771 | 2(Loss) | true |
| simdjson (ondemand) | 1993.8 | 0.139373 | 976.978ms | 18245 | 2560 | 378721 | 8726.93 | 0.122706 | 1.23716 | 3(Loss) | true |
| Glaze | 1802.02 | 0.137399 | 1064.49ms | 18245 | 4890 | 860683 | 9655.72 | 0.0185572 | 1.36993 | 4(Loss) | true |
