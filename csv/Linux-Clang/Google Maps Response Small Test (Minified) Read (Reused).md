
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2609.02 | 0.055754 | 183.458ms | 4390 | 160 | 128.07 | 1604.67 | 0.0303892 | 0.933403 | 1(Win) | true |
| Jsonifier (two-stage) | 2077.75 | 0.0334514 | 224.963ms | 4390 | 320 | 145.385 | 2014.98 | 0.22445 | 1.17614 | 2(Loss) | true |
| Glaze | 1939.97 | 0.320488 | 236.336ms | 4390 | 1280 | 61231.6 | 2158.1 | 0.204227 | 1.26114 | 3(Loss) | true |
| simdjson (ondemand) | 1094.13 | 0.1141 | 405.604ms | 4390 | 80 | 1524.93 | 3826.44 | 0.0251476 | 2.24714 | 4(Loss) | true |
