
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5606.61 | 0.219635 | 67.5917ms | 3808 | 1280 | 2590.64 | 647.734 | 1.03843 | 0.526555 | 1(Win) | true |
| Jsonifier (two-stage) | 5542.94 | 0.169127 | 67.3653ms | 3808 | 4890 | 6004.11 | 655.174 | 0.283706 | 0.533557 | 2(Loss) | true |
| simdjson (ondemand) | 4806.57 | 0.322843 | 77.8598ms | 3808 | 1280 | 7615.81 | 755.547 | 0.176093 | 0.617601 | 3(Loss) | true |
| Glaze | 3327.92 | 0.235314 | 112.436ms | 3808 | 160 | 1055.03 | 1091.25 | 0.228571 | 0.901142 | 4(Loss) | true |
