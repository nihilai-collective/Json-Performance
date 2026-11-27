
----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2269.94 | 0.203843 | 2837.68ms | 56369 | 320 | 745749 | 23682.4 | 0.0168873 | 1(Win) | true |
| simdjson (ondemand) | 1747.33 | 0.181763 | 3638.52ms | 56369 | 320 | 1.00068e+06 | 30765.6 | 0.153183 | 2(Loss) | true |
