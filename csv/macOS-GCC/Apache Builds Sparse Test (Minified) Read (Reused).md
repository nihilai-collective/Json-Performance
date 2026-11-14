
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2243.68 | 0.181829 | 4844.48ms | 94653 | 2560 | 1.36997e+07 | 40232.1 | 0.944154 | 1(Win) | true |
| simdjson (ondemand) | 1340.98 | 0.334719 | 8011.67ms | 94653 | 80 | 4.06141e+06 | 67315.2 | 0.0380156 | 2(Loss) | true |
