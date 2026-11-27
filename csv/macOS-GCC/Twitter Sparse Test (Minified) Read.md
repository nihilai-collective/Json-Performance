
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4435.37 | 0.177115 | 5792.54ms | 264040 | 320 | 3.23548e+06 | 56772.8 | 0.0225409 | 1(Win) | true |
| simdjson (ondemand) | 3783.9 | 0.248149 | 7121.62ms | 264040 | 80 | 2.1816e+06 | 66547.2 | 0.421375 | 2(Loss) | true |
