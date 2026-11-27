
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8083.89 | 0.0729731 | 3144.38ms | 264040 | 4890 | 2.52658e+06 | 31149.4 | 0.492225 | 0.306005 | 1(Win) | true |
| simdjson (ondemand) | 7314.57 | 0.0898918 | 3418.71ms | 264040 | 1280 | 1.22578e+06 | 34425.5 | 0.663467 | 0.338224 | 2(Loss) | true |
