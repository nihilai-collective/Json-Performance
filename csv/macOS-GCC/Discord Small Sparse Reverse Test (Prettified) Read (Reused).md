
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3156.15 | 0.522547 | 222.39ms | 6701 | 320 | 35823.3 | 2024.8 | 0.277338 | 1(Win) | true |
| simdjson (ondemand) | 2125.54 | 0.174199 | 317.214ms | 6701 | 4890 | 134135 | 3006.56 | 1.76207 | 2(Loss) | true |
