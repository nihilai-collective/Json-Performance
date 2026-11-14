
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1994.32 | 0.604621 | 236.19ms | 4857 | 1280 | 252421 | 2322.6 | 0.709644 | 1(Win) | true |
| simdjson (ondemand) | 1365.22 | 0.235517 | 337.139ms | 4857 | 4890 | 312239 | 3392.86 | 0.786116 | 2(Loss) | true |
