
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1932.73 | 0.105516 | 330.893ms | 5094 | 80 | 562.732 | 2513.55 | 0.000994599 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.31 | 0.0441156 | 411.515ms | 5094 | 160 | 347.939 | 3342.72 | 0.0334795 | 2(Loss) | true |
| Glaze | 1111.23 | 0.109098 | 514.208ms | 5094 | 2560 | 58234.4 | 4371.75 | 0.0210469 | 3(Loss) | true |
| simdjson (ondemand) | 790.194 | 0.147302 | 690.762ms | 5094 | 40 | 3280.42 | 6147.88 | 0.00718457 | 4(Loss) | true |
