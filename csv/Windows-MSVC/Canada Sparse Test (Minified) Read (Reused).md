
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8338.08 | 0.0513037 | 6108.24ms | 2090234 | 1280 | 1.92559e+07 | 239072 | 0.149769 | 0.364365 | 1(Win) | true |
| simdjson (ondemand) | 6420.38 | 0.140897 | 7961.28ms | 2090234 | 160 | 3.06193e+07 | 310481 | 0.231963 | 0.473234 | 2(Loss) | true |
