
----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 783.167 | 0.0898313 | 1019.85ms | 8150 | 1280 | 101735 | 9924.38 | 0.097518 | 3.87148 | 1(Win) | true |
| simdjson (ondemand) | 552.609 | 0.366809 | 1443.46ms | 8150 | 80 | 212937 | 14065 | 0.213751 | 5.49063 | 2(Loss) | true |
