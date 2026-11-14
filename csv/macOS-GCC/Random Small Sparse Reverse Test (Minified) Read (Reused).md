
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1533.49 | 1.62669 | 367.556ms | 4926 | 30 | 74500.1 | 3063.47 | 0.828729 | 1(Win) | true |
| simdjson (ondemand) | 896.51 | 0.353952 | 543.35ms | 4926 | 4890 | 1.68219e+06 | 5240.09 | 0.21793 | 2(Loss) | true |
