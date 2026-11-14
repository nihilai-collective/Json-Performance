
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1776.04 | 0.11775 | 140.807ms | 2158 | 4890 | 9103.83 | 1158.77 | 0.34739 | 1.68428 | 1(Win) | true |
| Glaze | 1751.86 | 0.120598 | 143.392ms | 2158 | 4890 | 9815.09 | 1174.76 | 0.278601 | 1.70705 | 2(Loss) | true |
| Jsonifier | 1460.12 | 0.158806 | 174.233ms | 2158 | 4890 | 24499.8 | 1409.49 | 0.0805492 | 2.05263 | 3(Loss) | true |
| simdjson (ondemand) | 1149.86 | 0.0885658 | 199.589ms | 2158 | 4890 | 12287.3 | 1789.82 | 0.273613 | 2.61612 | 4(Loss) | true |
