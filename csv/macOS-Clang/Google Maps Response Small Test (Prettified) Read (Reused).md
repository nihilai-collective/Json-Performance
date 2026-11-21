
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2869.81 | 0.0557174 | 347.784ms | 9378 | 160 | 482.409 | 3116.43 | 0.0244612 | 1(Win) | true |
| Jsonifier (two-stage) | 2373.81 | 0.104811 | 459.468ms | 9378 | 2560 | 39919.4 | 3767.6 | 1.74584 | 2(Loss) | true |
| Glaze | 1825.36 | 0.158309 | 532.345ms | 9378 | 320 | 19252.3 | 4899.61 | 0.0714853 | 3(Loss) | true |
| simdjson (ondemand) | 1631.38 | 0.437353 | 566.356ms | 9378 | 1280 | 735840 | 5482.2 | 0.358101 | 4(Loss) | true |
