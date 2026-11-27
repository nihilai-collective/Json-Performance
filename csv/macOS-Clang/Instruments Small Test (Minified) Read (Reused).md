
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1366.56 | 0.0949924 | 342.277ms | 4669 | 30 | 287.402 | 3258.33 | 0.0848384 | 1(Win) | true |
| simdjson (ondemand) | 1175.02 | 0.0370892 | 397.08ms | 4669 | 320 | 632.117 | 3789.46 | 0.106659 | 2(Loss) | true |
