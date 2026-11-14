
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 893.126 | 0.0352345 | 1027.25ms | 2821 | 2560 | 2883.74 | 3012.25 | 0.0560936 | 5.84278 | 25.5108 | 4.6721 | 0.00174293 | 7.69895e-05 | 1.86935e-05 | 1(Win) | true |
| simdjson (ondemand) | 362.244 | 0.055919 | 1467.5ms | 2821 | 1280 | 22076.7 | 7426.81 | 0.0689696 | 14.2933 | 66.5409 | 11.4272 | 0.0132012 | 0.000147609 | 7.58818e-05 | 2(Loss) | true |
