
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20790.2 | 0.180915 | 3399.07ms | 728486 | 320 | 1.16956e+06 | 33416.6 | 0.0376826 | 0.118989 | 1(Win) | true |
| simdjson (stage-1) | 19446.3 | 0.113186 | 3580.66ms | 728486 | 2560 | 4.18597e+06 | 35726 | 0.010737 | 0.127218 | 2(Loss) | true |
