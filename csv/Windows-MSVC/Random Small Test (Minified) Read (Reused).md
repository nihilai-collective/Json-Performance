
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 877.802 | 0.329593 | 661.405ms | 5094 | 2560 | 851766 | 5534.3 | 0.0648938 | 2.80548 | 1(Win) | true |
| Jsonifier (two-stage) | 807.818 | 0.0902723 | 769.61ms | 5094 | 160 | 4715.41 | 6013.75 | 0.187422 | 3.04966 | 2(Loss) | true |
| Glaze | 763.689 | 0.41486 | 746.096ms | 5094 | 640 | 445726 | 6361.25 | 0.157449 | 3.22828 | 3(Loss) | true |
| simdjson (ondemand) | 572.626 | 0.300575 | 1013.89ms | 5094 | 1280 | 832324 | 8483.75 | 0.0460651 | 4.30926 | 4(Loss) | true |
