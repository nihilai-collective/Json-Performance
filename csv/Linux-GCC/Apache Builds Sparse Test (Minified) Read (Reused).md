
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3821.25 | 0.0191686 | 3604.66ms | 94653 | 4890 | 100265 | 23622.7 | 0.0666092 | 1.33129 | 6.99845 | 1.20952 | 0.00230259 | 5.25005e-06 | 2.55157e-06 | 1(Win) | true |
| simdjson (ondemand) | 2306.16 | 0.0594446 | 5177.86ms | 94653 | 320 | 173246 | 39142.1 | 0.204802 | 2.22599 | 8.83642 | 1.55045 | 0.00710711 | 3.05062e-05 | 2.41012e-05 | 2(Loss) | true |
