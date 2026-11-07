
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2966.92 | 0.195517 | 304.13ms | 8051 | 2560 | 65538.1 | 2587.88 | 0.12986 | 0.825639 | 1(Win) | true |
| Jsonifier | 2214.3 | 0.0372754 | 396.575ms | 8051 | 160 | 267.295 | 3467.47 | 0.0736666 | 1.11001 | 2(Loss) | true |
| Glaze | 2067.73 | 0.0939482 | 421.674ms | 8051 | 30 | 365.099 | 3713.27 | 0.152839 | 1.18863 | 3(Loss) | true |
| simdjson (ondemand) | 1507.48 | 0.113179 | 557.708ms | 8051 | 4890 | 162494 | 5093.28 | 0.260343 | 1.63307 | 4(Loss) | true |
