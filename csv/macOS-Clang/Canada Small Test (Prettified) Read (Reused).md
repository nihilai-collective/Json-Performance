
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1161.16 | 0.101608 | 1089.37ms | 11579 | 2560 | 239029 | 9509.93 | 0.114119 | 1(Win) | true |
| simdjson (ondemand) | 1145.79 | 0.0493092 | 1085.49ms | 11579 | 40 | 903.333 | 9637.52 | 0.0438583 | 2(Loss) | true |
