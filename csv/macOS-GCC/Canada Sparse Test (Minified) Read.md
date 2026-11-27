
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4693.4 | 0.109017 | 5628.99ms | 2090234 | 320 | 6.86045e+07 | 424725 | 0.0831847 | 1(Win) | true |
| simdjson (ondemand) | 3569.03 | 0.271002 | 7094.22ms | 2090234 | 40 | 9.1642e+07 | 558528 | 0.112421 | 2(Loss) | true |
