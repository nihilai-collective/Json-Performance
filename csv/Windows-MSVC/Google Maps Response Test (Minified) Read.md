
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1371.51 | 0.202693 | 815.684ms | 11812 | 320 | 88690.3 | 8213.44 | 0.0799634 | 2.21062 | 1(Win) | true |
| Jsonifier (two-stage) | 1184.68 | 0.249033 | 941.752ms | 11812 | 80 | 44859.2 | 9508.75 | 0.0394529 | 2.5588 | 2(Loss) | true |
| Glaze | 976.814 | 0.137064 | 1161.55ms | 11812 | 640 | 159901 | 11532.2 | 0.0866387 | 3.10551 | 3(Loss) | true |
| simdjson (ondemand) | 599.311 | 0.194061 | 1889.32ms | 11812 | 80 | 106441 | 18796.2 | 0.0465302 | 5.06569 | 4(Loss) | true |
