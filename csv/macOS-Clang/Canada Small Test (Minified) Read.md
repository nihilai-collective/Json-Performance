
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 482.818 | 0.0352352 | 927.264ms | 4630 | 80 | 830.688 | 9145.29 | 0.108233 | 1(Win) | true |
| simdjson (ondemand) | 454.572 | 0.0535496 | 984.943ms | 4630 | 40 | 1082.25 | 9713.55 | 0.0406814 | 2(Loss) | true |
