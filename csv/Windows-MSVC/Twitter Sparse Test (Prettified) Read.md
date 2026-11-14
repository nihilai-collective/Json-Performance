
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6272.77 | 0.0567763 | 5496.31ms | 360584 | 2560 | 2.4801e+06 | 54821 | 0.0494752 | 0.484313 | 1(Win) | true |
| simdjson (ondemand) | 4609.38 | 0.106633 | 7457.87ms | 360584 | 640 | 4.05034e+06 | 74604.4 | 0.0456784 | 0.659162 | 2(Loss) | true |
