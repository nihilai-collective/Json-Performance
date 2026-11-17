
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2233.93 | 0.583597 | 1065.87ms | 18245 | 30 | 61986.3 | 7788.87 | 0.338651 | 1(Win) | true |
| Jsonifier (two-stage) | 1923.8 | 0.335748 | 1048.81ms | 18245 | 2560 | 2.36067e+06 | 9044.49 | 1.50547 | 2(Loss) | true |
| Glaze | 1296.95 | 0.193059 | 1572.73ms | 18245 | 1280 | 858678 | 13415.9 | 0.398757 | 3(Loss) | true |
| simdjson (ondemand) | 1249.13 | 0.171218 | 1561.77ms | 18245 | 2560 | 1.45618e+06 | 13929.6 | 0.315579 | 4(Loss) | true |
