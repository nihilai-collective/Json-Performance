
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 754.763 | 0.279124 | 592.481ms | 4630 | 2560 | 682614 | 5850.2 | 1.17572 | 1(Win) | true |
| Jsonifier (two-stage) | 622.534 | 0.79707 | 726.827ms | 4630 | 320 | 1.02277e+06 | 7092.8 | 0.795816 | 2(Loss) | true |
| simdjson (reflection) | 574.557 | 0.121778 | 775.54ms | 4630 | 4890 | 428297 | 7685.08 | 0.0361626 | 3(Loss) | true |
| Glaze | 515.686 | 0.420487 | 883.66ms | 4630 | 320 | 414807 | 8562.4 | 0.0093423 | 4(Loss) | true |
| simdjson (ondemand) | 411.434 | 0.403029 | 1047.06ms | 4630 | 1280 | 2.39466e+06 | 10732 | 0.138096 | 5(Loss) | true |
