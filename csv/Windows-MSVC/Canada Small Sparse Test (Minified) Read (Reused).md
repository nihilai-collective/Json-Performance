
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7612.68 | 0.181646 | 60.1154ms | 4630 | 4890 | 5428.1 | 580.02 | 0.0304737 | 0.385703 | 1(Win) | true |
| simdjson (ondemand) | 5359.78 | 0.133077 | 84.4142ms | 4630 | 4890 | 5877.38 | 823.824 | 0.342077 | 0.554219 | 2(Loss) | true |
