
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1919.99 | 0.0971023 | 328.028ms | 5094 | 80 | 482.911 | 2530.22 | 0.0819413 | 1(Win) | true |
| Jsonifier (two-stage) | 1424.78 | 0.0844689 | 443.215ms | 5094 | 30 | 248.851 | 3409.67 | 0.147402 | 2(Loss) | true |
| Glaze | 1117.22 | 0.0757443 | 513.403ms | 5094 | 320 | 3471.29 | 4348.31 | 0.105972 | 3(Loss) | true |
| simdjson (ondemand) | 787.194 | 0.295968 | 690.981ms | 5094 | 640 | 213513 | 6171.31 | 0.418976 | 4(Loss) | true |
