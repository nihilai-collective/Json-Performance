
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5492.91 | 0.0320663 | 4604.47ms | 264040 | 4890 | 1.05667e+06 | 45842.4 | 0.0750222 | 0.553022 | 1(Win) | true |
| simdjson (ondemand) | 3756.61 | 0.0284657 | 6706.27ms | 264040 | 4890 | 1.78033e+06 | 67030.7 | 0.0146149 | 0.808789 | 2(Loss) | true |
