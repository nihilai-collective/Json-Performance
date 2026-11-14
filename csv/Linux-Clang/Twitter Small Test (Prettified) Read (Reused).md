
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3010.13 | 0.229999 | 862.112ms | 3808 | 4890 | 37651.6 | 1206.46 | 0.0876698 | 1.73902 | 6.17358 | 0.871324 | 0.000531493 | 3.68399e-05 | 8.6461e-06 | 1(Win) | true |
| Glaze | 2726.78 | 0.214297 | 877.402ms | 3808 | 2560 | 20852.8 | 1331.82 | 0.182737 | 1.91116 | 7.88524 | 1.36371 | 0.00043494 | 2.0516e-05 | 2.66708e-06 | 2(Loss) | true |
| Jsonifier | 1999.5 | 0.212311 | 925.832ms | 3808 | 4890 | 72711.9 | 1816.25 | 0.050386 | 2.58562 | 6.63944 | 1.23477 | 0.000532191 | 4.26398e-05 | 6.06838e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1355.34 | 0.172011 | 1012.75ms | 3808 | 1280 | 27190.9 | 2679.48 | 0.0120141 | 3.78539 | 12.8288 | 2.1124 | 0.000544085 | 4.12372e-05 | 8.00125e-06 | 4(Loss) | true |
