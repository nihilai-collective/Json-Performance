
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12503.4 | 0.216426 | 90.7253ms | 11579 | 4890 | 17865.6 | 883.17 | 0.071461 | 0.238223 | 1(Win) | true |
| simdjson (ondemand) | 8830.46 | 0.119764 | 127.055ms | 11579 | 4890 | 10968.2 | 1250.51 | 0.481572 | 0.339109 | 2(Loss) | true |
