
----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3532.5 | 0.177193 | 7230.37ms | 2090234 | 640 | 6.3988e+08 | 564304 | 0.218654 | 1(Win) | true |
| simdjson (ondemand) | 2794.81 | 0.242526 | 9266.83ms | 2090234 | 320 | 9.57531e+08 | 713252 | 0.0685637 | 2(Loss) | true |
