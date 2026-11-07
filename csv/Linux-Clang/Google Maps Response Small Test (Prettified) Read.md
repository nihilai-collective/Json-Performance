
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3671.49 | 0.0607927 | 248.443ms | 9378 | 80 | 175.441 | 2435.95 | 0.133596 | 0.667116 | 1(Win) | true |
| Jsonifier | 3155.7 | 0.0892057 | 287.901ms | 9378 | 160 | 1022.67 | 2834.1 | 0.151494 | 0.777362 | 2(Loss) | true |
| Glaze | 2534.96 | 0.0505279 | 356.184ms | 9378 | 80 | 254.233 | 3528.09 | 0.204014 | 0.969608 | 3(Loss) | true |
| simdjson (ondemand) | 2058.67 | 0.317409 | 438.759ms | 9378 | 640 | 121693 | 4344.34 | 0.0376349 | 1.19507 | 4(Loss) | true |
