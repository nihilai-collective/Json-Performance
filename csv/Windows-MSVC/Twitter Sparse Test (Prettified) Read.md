
----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7194.36 | 0.142493 | 4823.6ms | 360584 | 4890 | 2.26842e+07 | 47798.5 | 0.276782 | 0.422232 | 1(Win) | true |
| simdjson (ondemand) | 4680.98 | 0.0943617 | 7356.15ms | 360584 | 4890 | 2.34985e+07 | 73463.2 | 0.140197 | 0.649082 | 2(Loss) | true |
