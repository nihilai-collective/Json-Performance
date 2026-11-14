
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1957.48 | 0.127067 | 900.78ms | 18245 | 1280 | 163294 | 8888.86 | 0.0496776 | 1(Win) | true |
| Jsonifier | 1936.53 | 0.0706586 | 928.958ms | 18245 | 4890 | 197097 | 8985.05 | 0.23619 | 2(Loss) | true |
| Glaze | 1229.06 | 0.0730248 | 1442.06ms | 18245 | 30 | 3206.27 | 14156.9 | 0.176046 | 3(Loss) | true |
| simdjson (ondemand) | 1219.01 | 0.0735192 | 1446.09ms | 18245 | 30 | 3303.67 | 14273.7 | 0.0879633 | 4(Loss) | true |
