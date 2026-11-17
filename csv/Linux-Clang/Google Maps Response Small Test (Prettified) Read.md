
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2373.27 | 0.025696 | 1097.53ms | 9378 | 4890 | 4585.28 | 3768.46 | 0.131636 | 2.19258 | 9.36257 | 1.69727 | 0.00145079 | 1.97783e-05 | 3.40177e-06 | 1(Win) | true |
| simdjson (ondemand) | 2123.99 | 0.0730339 | 1140.16ms | 9378 | 160 | 1513.16 | 4210.74 | 0.0118758 | 2.44915 | 10.2488 | 1.69834 | 0.0019667 | 1.73278e-05 | 1.33291e-06 | 2(Loss) | true |
