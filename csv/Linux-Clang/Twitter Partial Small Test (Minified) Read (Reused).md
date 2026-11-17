
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6503.16 | 0.075496 | 47.1127ms | 2889 | 320 | 32.7374 | 423.666 | 0.35793 | 0.354458 | 1(Win) | true |
| Jsonifier | 6396.05 | 0.0424473 | 46.9359ms | 2889 | 1280 | 42.7939 | 430.76 | 0.0719503 | 0.361788 | 2(Loss) | true |
| Jsonifier (two-stage) | 6365.68 | 0.0805721 | 47.2365ms | 2889 | 320 | 38.9157 | 432.816 | 0.466403 | 0.363799 | 3(Loss) | true |
| Glaze | 3228.41 | 0.088895 | 89.6392ms | 2889 | 80 | 46.0429 | 853.413 | 0.0454266 | 0.742445 | 4(Loss) | true |
