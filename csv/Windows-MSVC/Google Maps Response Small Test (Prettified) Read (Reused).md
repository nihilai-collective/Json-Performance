
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2149.74 | 0.210942 | 475.187ms | 9378 | 4890 | 376606 | 4160.31 | 0.169796 | 1.14383 | 1(Win) | true |
| Jsonifier (two-stage) | 2123.1 | 0.193594 | 518.533ms | 9378 | 40 | 2660.26 | 4212.5 | 0.297619 | 1.15486 | 2(Loss) | true |
| Glaze | 1596.35 | 0.527909 | 614.314ms | 9378 | 640 | 559837 | 5602.5 | 0.0613189 | 1.54336 | 3(Loss) | true |
| simdjson (ondemand) | 1125.45 | 0.20628 | 858.733ms | 9378 | 2560 | 687898 | 7946.68 | 0.14676 | 2.1922 | 4(Loss) | true |
