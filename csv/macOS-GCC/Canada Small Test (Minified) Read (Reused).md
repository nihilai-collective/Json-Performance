
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 593.577 | 0.127398 | 863.716ms | 4630 | 4890 | 439176 | 7438.82 | 0.173926 | 1(Win) | true |
| simdjson (ondemand) | 572.098 | 0.177148 | 886.964ms | 4630 | 2560 | 478556 | 7718.1 | 0.112595 | 2(Loss) | true |
