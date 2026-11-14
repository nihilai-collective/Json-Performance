
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7414.97 | 0.427495 | 3269.38ms | 264040 | 80 | 1.68606e+06 | 33959.4 | 0.951714 | 0.333626 | 1(Win) | true |
| simdjson (ondemand) | 6855.69 | 0.061496 | 3645.18ms | 264040 | 4890 | 2.49483e+06 | 36729.8 | 0.0837719 | 0.360852 | 2(Loss) | true |
