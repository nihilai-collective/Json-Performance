
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4386.38 | 0.0750581 | 69.7873ms | 2889 | 640 | 142.252 | 628.119 | 0.062151 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4382.23 | 0.0600106 | 69.7843ms | 2889 | 1280 | 182.209 | 628.713 | 0.0515952 | 1(Tie) | true |
| simdjson (ondemand) | 3803.57 | 0.160664 | 80.7271ms | 2889 | 320 | 433.411 | 724.362 | 0.0120781 | 3(Loss) | true |
| Glaze | 2307.86 | 0.13933 | 125.228ms | 2889 | 160 | 442.678 | 1193.82 | 0.12528 | 4(Loss) | true |
