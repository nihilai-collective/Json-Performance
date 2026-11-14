
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1576.11 | 0.159616 | 334.652ms | 4926 | 2560 | 57944.1 | 2980.62 | 0.27861 | 1.91575 | 1(Win) | true |
| simdjson (ondemand) | 1433.55 | 0.177855 | 363.873ms | 4926 | 640 | 21740.8 | 3277.03 | 0.0714694 | 2.10847 | 2(Loss) | true |
