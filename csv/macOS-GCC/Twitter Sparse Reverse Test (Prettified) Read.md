
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3684.97 | 0.0704316 | 9900.25ms | 360584 | 1280 | 5.52956e+06 | 93319.6 | 0.142509 | 1(Win) | true |
| simdjson (ondemand) | 2861.7 | 0.906759 | 6603.41ms | 360584 | 30 | 3.56181e+07 | 120166 | 0.0567779 | 2(Loss) | true |
