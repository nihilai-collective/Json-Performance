
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1997.68 | 0.166701 | 427.378ms | 7932 | 30 | 1195.4 | 3786.67 | 0.438212 | 1.23105 | 1(Win) | true |
| Jsonifier | 1639.01 | 0.350521 | 473.776ms | 7932 | 1280 | 334996 | 4615.31 | 0.850149 | 1.50188 | 2(Loss) | true |
| Glaze | 1430.65 | 0.100156 | 558.335ms | 7932 | 40 | 1121.79 | 5287.5 | 0.205306 | 1.72079 | 3(Loss) | true |
| simdjson (ondemand) | 1346 | 0.11397 | 609.087ms | 7932 | 40 | 1641.03 | 5620 | 0.237812 | 1.83041 | 4(Loss) | true |
