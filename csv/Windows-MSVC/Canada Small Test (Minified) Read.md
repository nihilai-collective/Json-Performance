
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 504.868 | 0.054481 | 877.175ms | 4630 | 4890 | 111021 | 8745.87 | 0.118108 | 6.00686 | 1(Win) | true |
| Jsonifier (two-stage) | 503.071 | 0.11928 | 882.355ms | 4630 | 1280 | 140297 | 8777.11 | 0.0650195 | 6.0284 | 2(Loss) | true |
| simdjson (ondemand) | 308.723 | 0.0948332 | 1425.33ms | 4630 | 640 | 117740 | 14302.5 | 0.0196683 | 9.83194 | 3(Loss) | true |
| Glaze | 306.297 | 0.045185 | 1446.35ms | 4630 | 4890 | 207480 | 14415.8 | 0.0535937 | 9.90931 | 4(Loss) | true |
