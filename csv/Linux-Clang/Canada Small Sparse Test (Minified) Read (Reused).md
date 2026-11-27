
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6805.73 | 0.221497 | 780.77ms | 4630 | 4890 | 10098.5 | 648.793 | 1.1959 | 0.801199 | 3.61641 | 0.49676 | 0.000446232 | 2.01849e-05 | 8.65698e-06 | 1(Win) | true |
| simdjson (ondemand) | 6748.13 | 0.102437 | 782.511ms | 4630 | 160 | 71.8833 | 654.331 | 0.0296192 | 0.811258 | 4.0689 | 0.485097 | 0.000431965 | 5.39957e-06 | 1.34989e-06 | 2(Loss) | true |
