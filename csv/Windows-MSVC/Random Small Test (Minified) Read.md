
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 740.287 | 0.401118 | 667.352ms | 5094 | 640 | 443447 | 6562.34 | 0.183674 | 3.3219 | 1(Win) | true |
| Jsonifier (two-stage) | 666.609 | 0.436458 | 736.83ms | 5094 | 640 | 647500 | 7287.66 | 0.074985 | 3.6906 | 2(Loss) | true |
| Glaze | 595.163 | 0.186684 | 830.14ms | 5094 | 80 | 18575.9 | 8162.5 | 0.0919681 | 4.12924 | 3(Loss) | true |
| simdjson (ondemand) | 473.993 | 0.277103 | 1045.24ms | 5094 | 1280 | 1.03245e+06 | 10249.1 | 0.0969007 | 5.19844 | 4(Loss) | true |
