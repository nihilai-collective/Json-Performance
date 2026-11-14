
----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5706.91 | 0.229018 | 66.1544ms | 3770 | 1280 | 2664.58 | 630 | 0 | 0.517511 | 1(Win) | true |
| simdjson (ondemand) | 4658.89 | 0.164434 | 80.5055ms | 3770 | 1280 | 2061.16 | 771.719 | 0.141529 | 0.640286 | 2(Loss) | true |
