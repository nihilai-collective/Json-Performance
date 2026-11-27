
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9859.46 | 0.571886 | 125.827ms | 11579 | 40 | 1641.03 | 1120 | 0.591716 | 0.303942 | 1(Win) | true |
| simdjson (ondemand) | 7698.96 | 1.0531 | 146.013ms | 11579 | 1280 | 292028 | 1434.3 | 0.125436 | 0.38998 | 2(Loss) | true |
