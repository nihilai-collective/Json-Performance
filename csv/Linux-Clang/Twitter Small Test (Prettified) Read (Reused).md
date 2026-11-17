
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2926.7 | 0.0493279 | 846.289ms | 3770 | 640 | 235.013 | 1228.47 | 0.0288807 | 1.81921 | 6.90981 | 1.1679 | 0.000625829 | 6.92142e-05 | 1.98939e-05 | 1(Win) | true |
| simdjson (ondemand) | 2723.81 | 0.127053 | 858.507ms | 3770 | 640 | 1800.03 | 1319.97 | 0.0102996 | 1.9493 | 7.48276 | 1.09416 | 0.000524702 | 3.48143e-05 | 6.21684e-06 | 2(Loss) | true |
