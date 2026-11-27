
----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1601.09 | 0.166588 | 5682.64ms | 94653 | 640 | 5.64551e+06 | 56379.2 | 0.0454274 | 1(Win) | true |
| simdjson (ondemand) | 1092.77 | 0.20868 | 8478.96ms | 94653 | 80 | 2.37717e+06 | 82604.8 | 0.470389 | 2(Loss) | true |
