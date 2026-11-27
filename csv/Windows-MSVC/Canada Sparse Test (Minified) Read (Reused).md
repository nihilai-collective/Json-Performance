
----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7599.32 | 0.103548 | 6676.04ms | 2090234 | 1280 | 9.44358e+07 | 262313 | 0.281795 | 0.399764 | 1(Win) | true |
| simdjson (ondemand) | 6400.42 | 0.0832026 | 7972.28ms | 2090234 | 640 | 4.29761e+07 | 311449 | 0.0204145 | 0.474735 | 2(Loss) | true |
