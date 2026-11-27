
----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3165.38 | 0.121145 | 8200.64ms | 264040 | 1280 | 1.18881e+07 | 79550.6 | 0.184625 | 1(Win) | true |
| simdjson (ondemand) | 2407.71 | 0.200706 | 5360.16ms | 264040 | 320 | 1.40994e+07 | 104584 | 0.200012 | 2(Loss) | true |
