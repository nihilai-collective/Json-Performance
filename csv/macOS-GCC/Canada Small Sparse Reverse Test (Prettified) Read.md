
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5513.58 | 0.430185 | 203.745ms | 11579 | 2560 | 190031 | 2002.8 | 0.477042 | 1(Win) | true |
| simdjson (ondemand) | 4927.53 | 0.569964 | 220.764ms | 11579 | 1280 | 208828 | 2241 | 0.782515 | 2(Loss) | true |
