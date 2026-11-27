
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3206.35 | 1.58065 | 5267.81ms | 360584 | 320 | 9.19629e+08 | 107250 | 0.485706 | 1(Win) | true |
| simdjson (ondemand) | 3003.31 | 0.526467 | 5934.4ms | 360584 | 30 | 1.09013e+07 | 114500 | 0.059657 | 2(Loss) | true |
