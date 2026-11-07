
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6559.1 | 0.324442 | 59.2814ms | 3808 | 1280 | 4130.37 | 553.672 | 0.354007 | 0.359198 | 1(Win) | true |
| Jsonifier (two-stage) | 6457.4 | 0.498087 | 59.6241ms | 3808 | 4890 | 38370.6 | 562.393 | 0.30985 | 0.365313 | 2(Loss) | true |
| simdjson (ondemand) | 3534.8 | 0.386157 | 105.808ms | 3808 | 2560 | 40293.3 | 1027.38 | 0.0494522 | 0.68278 | 3(Loss) | true |
| Glaze | 3366.48 | 0.300736 | 114.688ms | 3808 | 160 | 1683.96 | 1078.75 | 0.231214 | 0.714373 | 4(Loss) | true |
