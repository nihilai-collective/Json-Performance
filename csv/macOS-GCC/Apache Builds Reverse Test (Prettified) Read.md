
----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1047.26 | 0.122807 | 5872.37ms | 124597 | 640 | 1.2426e+07 | 113463 | 0.249327 | 1(Win) | true |
| simdjson (ondemand) | 609.474 | 0.208382 | 5010.29ms | 124597 | 160 | 2.64086e+07 | 194963 | 0.299465 | 2(Loss) | true |
