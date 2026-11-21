
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1888.01 | 0.124647 | 627.164ms | 8051 | 2560 | 65779.5 | 4066.72 | 0.332877 | 1(Win) | true |
| Jsonifier | 1822.11 | 0.422871 | 517.161ms | 8051 | 640 | 203210 | 4213.81 | 1.81592 | 2(Loss) | true |
| Glaze | 1310.82 | 0.368565 | 710.506ms | 8051 | 1280 | 596557 | 5857.42 | 0.755239 | 3(Loss) | true |
| simdjson (ondemand) | 970.233 | 0.399472 | 913.16ms | 8051 | 1280 | 1.27917e+06 | 7913.6 | 1.73241 | 4(Loss) | true |
