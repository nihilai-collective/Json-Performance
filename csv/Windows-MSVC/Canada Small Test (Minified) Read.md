
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 601.734 | 0.174214 | 759.202ms | 4630 | 4890 | 799153 | 7337.98 | 0.097231 | 4.09771 | 1(Win) | true |
| Jsonifier (two-stage) | 569.009 | 0.21932 | 798.087ms | 4630 | 30 | 8689.66 | 7760 | 0.0859845 | 4.33256 | 2(Loss) | true |
| Glaze | 174.614 | 0.196183 | 2552.5ms | 4630 | 1280 | 3.15018e+06 | 25287.3 | 0.256777 | 14.1612 | 3(Loss) | true |
| simdjson (ondemand) | 172.171 | 0.0840319 | 2586.48ms | 4630 | 4890 | 2.27112e+06 | 25646.1 | 0.00883217 | 14.3626 | 4(Loss) | true |
