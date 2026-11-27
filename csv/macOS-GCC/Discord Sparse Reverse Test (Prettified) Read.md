
----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1999.6 | 0.0693569 | 4169.42ms | 83958 | 4890 | 3.77162e+06 | 40042.4 | 0.174065 | 1(Win) | true |
| simdjson (ondemand) | 1393.78 | 0.152958 | 5686.77ms | 83958 | 640 | 4.94156e+06 | 57447.2 | 0.0695807 | 2(Loss) | true |
