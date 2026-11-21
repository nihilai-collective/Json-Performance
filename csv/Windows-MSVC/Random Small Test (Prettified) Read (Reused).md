
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1329.32 | 0.239981 | 693.47ms | 8051 | 2560 | 491850 | 5775.9 | 0.186985 | 1.85337 | 1(Win) | true |
| Jsonifier | 1278.03 | 0.178423 | 762.71ms | 8051 | 4890 | 561867 | 6007.73 | 0.274415 | 1.92882 | 2(Loss) | true |
| Glaze | 1177.39 | 0.111456 | 836.328ms | 8051 | 80 | 4226.27 | 6521.25 | 0.0191718 | 2.0974 | 3(Loss) | true |
| simdjson (ondemand) | 979.977 | 0.158824 | 909.789ms | 8051 | 4890 | 757200 | 7834.91 | 0.0300826 | 2.51777 | 4(Loss) | true |
