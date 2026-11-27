
----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1493.18 | 0.0636304 | 3802.04ms | 56369 | 30 | 15743.7 | 36002.1 | 0.0710564 | 1(Win) | true |
| simdjson (ondemand) | 1034.07 | 0.0597723 | 5320.68ms | 56369 | 2560 | 2.47182e+06 | 51986.3 | 0.00634823 | 2(Loss) | true |
