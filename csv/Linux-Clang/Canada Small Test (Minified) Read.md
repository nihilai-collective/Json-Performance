
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 909.371 | 0.0488033 | 486.781ms | 4630 | 30 | 168.461 | 4855.57 | 0.0254069 | 2.70816 | 1(Win) | true |
| Jsonifier (two-stage) | 853.98 | 0.0402363 | 520.327ms | 4630 | 80 | 346.253 | 5170.51 | 0.11642 | 2.88448 | 2(Loss) | true |
| Glaze | 761.79 | 0.215478 | 583.512ms | 4630 | 2560 | 399334 | 5796.23 | 0.0043197 | 3.2355 | 3(Loss) | true |
| simdjson (ondemand) | 739.051 | 0.0868663 | 612.852ms | 4630 | 30 | 808.047 | 5974.57 | 0.429421 | 3.33433 | 4(Loss) | true |
