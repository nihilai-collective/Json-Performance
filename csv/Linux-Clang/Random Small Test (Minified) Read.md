
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1834.91 | 0.180321 | 268.006ms | 5094 | 4890 | 111453 | 2647.56 | 0.242368 | 1.33619 | 1(Win) | true |
| Jsonifier (two-stage) | 1523.73 | 0.512663 | 320.077ms | 5094 | 640 | 170980 | 3188.25 | 0.279494 | 1.61034 | 2(Loss) | true |
| Glaze | 1259.49 | 0.0736136 | 397.894ms | 5094 | 160 | 1289.94 | 3857.14 | 0.0050234 | 1.95264 | 3(Loss) | true |
| simdjson (ondemand) | 839.748 | 0.230694 | 580.584ms | 5094 | 1280 | 227984 | 5785.09 | 0.221708 | 2.93369 | 4(Loss) | true |
