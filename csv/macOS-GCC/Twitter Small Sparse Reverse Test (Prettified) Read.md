
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3343.89 | 2.88514 | 127.98ms | 3770 | 80 | 76984.1 | 1075.2 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3027.28 | 0.518845 | 122.349ms | 3770 | 4890 | 185679 | 1187.65 | 0.27453 | 2(Loss) | true |
