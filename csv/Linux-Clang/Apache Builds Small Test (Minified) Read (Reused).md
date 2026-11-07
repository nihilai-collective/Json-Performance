
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2993.53 | 0.104598 | 92.8636ms | 2632 | 40 | 30.7692 | 838.5 | 0.0476815 | 0.801814 | 1(Win) | true |
| Jsonifier (two-stage) | 2968.6 | 0.0289763 | 92.945ms | 2632 | 640 | 38.4179 | 845.539 | 0.053746 | 0.808305 | 2(Loss) | true |
| Glaze | 2459.05 | 0.0879574 | 109.687ms | 2632 | 40 | 32.2436 | 1020.75 | 0.0505908 | 0.981858 | 3(Loss) | true |
| simdjson (ondemand) | 1766.62 | 0.160497 | 154.328ms | 2632 | 30 | 156.006 | 1420.83 | 0.0468988 | 1.3734 | 4(Loss) | true |
