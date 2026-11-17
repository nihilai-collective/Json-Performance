
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1990.82 | 0.140934 | 1048.78ms | 18245 | 30 | 4551.72 | 8740 | 0.229358 | 1.23893 | 1(Win) | true |
| Jsonifier | 1586.12 | 0.114006 | 1266.72ms | 18245 | 40 | 6256.41 | 10970 | 0.152161 | 1.55679 | 2(Loss) | true |
| Glaze | 590.687 | 0.38936 | 3064.88ms | 18245 | 160 | 2.10473e+06 | 29456.9 | 0.0487763 | 4.18631 | 3(Loss) | true |
| simdjson (ondemand) | 385.297 | 0.152108 | 4836.04ms | 18245 | 1280 | 6.03966e+06 | 45159.4 | 0.0339192 | 6.42192 | 4(Loss) | true |
