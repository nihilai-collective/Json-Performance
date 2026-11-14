
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2426.43 | 0.0222514 | 1088.19ms | 9378 | 4890 | 3289.32 | 3685.89 | 0.0188035 | 2.1454 | 9.36255 | 1.69727 | 0.00127394 | 2.41831e-05 | 5.95311e-06 | 1(Win) | true |
| simdjson (ondemand) | 2137.57 | 0.0246728 | 1136.89ms | 9378 | 4890 | 5211.06 | 4183.98 | 0.0206983 | 2.43455 | 10.3172 | 1.70687 | 0.00167289 | 2.42267e-05 | 5.49517e-06 | 2(Loss) | true |
