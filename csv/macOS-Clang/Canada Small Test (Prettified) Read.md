
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1488.74 | 0.0387149 | 853.929ms | 11579 | 160 | 1319.41 | 7417.41 | 0.0520162 | 1(Win) | true |
| Jsonifier (two-stage) | 1266.86 | 0.12036 | 877.297ms | 11579 | 4890 | 538219 | 8716.5 | 0.121944 | 2(Loss) | true |
| simdjson (ondemand) | 968.367 | 0.400645 | 1128.45ms | 11579 | 640 | 1.33586e+06 | 11403.3 | 0.190342 | 3(Loss) | true |
| Glaze | 949.52 | 0.643064 | 1226.66ms | 11579 | 160 | 894874 | 11629.7 | 0.0989483 | 4(Loss) | true |
