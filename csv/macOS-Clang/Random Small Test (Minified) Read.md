
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1067.33 | 0.132243 | 449.793ms | 4926 | 30 | 1016.4 | 4401.47 | 0.0977902 | 1(Win) | true |
| simdjson (ondemand) | 711.002 | 0.729589 | 607.21ms | 4926 | 320 | 743625 | 6607.29 | 0.117676 | 2(Loss) | true |
