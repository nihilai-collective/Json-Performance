
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2573.48 | 0.179813 | 480.967ms | 11812 | 2560 | 158594 | 4377.26 | 0.0655896 | 0.955975 | 1(Win) | true |
| Glaze | 1873.63 | 0.0864585 | 733.187ms | 11812 | 40 | 1080.82 | 6012.27 | 0.35619 | 1.31578 | 2(Loss) | true |
| Jsonifier (two-stage) | 1867.81 | 0.104106 | 637.026ms | 11812 | 30 | 1182.65 | 6031.03 | 0.181059 | 1.31915 | 3(Loss) | true |
| simdjson (ondemand) | 944.298 | 0.259552 | 1258.8ms | 11812 | 640 | 613560 | 11929.3 | 0.197133 | 2.61335 | 4(Loss) | true |
