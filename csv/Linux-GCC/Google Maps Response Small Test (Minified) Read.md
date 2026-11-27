
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.98 | 0.0803894 | 234.821ms | 4390 | 80 | 291.889 | 2376.1 | 0.0946034 | 1.38926 | 1(Win) | true |
| Jsonifier (two-stage) | 1581.27 | 0.0460231 | 268.976ms | 4390 | 160 | 237.568 | 2647.63 | 0.475551 | 1.55031 | 2(Loss) | true |
| Glaze | 1562.19 | 0.381257 | 280.996ms | 4390 | 1280 | 133631 | 2679.97 | 0.368771 | 1.56949 | 3(Loss) | true |
| simdjson (reflection) | 1516.77 | 0.0634722 | 285.666ms | 4390 | 160 | 491.106 | 2760.22 | 0.15739 | 1.61738 | 4(Loss) | true |
| simdjson (ondemand) | 1306.69 | 0.243874 | 330.968ms | 4390 | 1280 | 78150 | 3204.01 | 0.118972 | 1.87716 | 5(Loss) | true |
