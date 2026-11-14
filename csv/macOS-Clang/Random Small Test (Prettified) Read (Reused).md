
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1901.03 | 0.0421608 | 443.66ms | 8150 | 160 | 475.419 | 4088.55 | 0.0113108 | 1(Win) | true |
| simdjson (ondemand) | 1443.41 | 0.096208 | 573.005ms | 8150 | 30 | 805.151 | 5384.77 | 0.00371432 | 2(Loss) | true |
