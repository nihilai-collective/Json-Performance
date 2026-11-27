
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1632.35 | 0.223777 | 7318.08ms | 124597 | 160 | 4.24558e+06 | 72793.6 | 0.0439406 | 1(Win) | true |
| simdjson (ondemand) | 1210.27 | 0.0751886 | 9729.3ms | 124597 | 4890 | 2.66478e+07 | 98180.3 | 0.187959 | 2(Loss) | true |
